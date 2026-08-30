import cv2
import numpy as np
from pathlib import Path
import cv2.ximgproc as xip

# =============================================================================
#                           Paths (project structure)
# =============================================================================
PROJECT_ROOT = Path(__file__).resolve().parents[1]

# Find dataset folder (must be "dataset")
DATASET_DIR = None
for name in ["dataset"]:
    candidate = PROJECT_ROOT / name
    if candidate.exists():
        DATASET_DIR = candidate
        break

if DATASET_DIR is None:
    raise FileNotFoundError(
        f"Dataset folder not found. Expected 'dataset' or 'Dataset' under: {PROJECT_ROOT}"
    )

OUTPUT_DIR = PROJECT_ROOT / "output"

# Input folders
HAZY_RAW_DIR = DATASET_DIR / "01. Hazy - Raw"
LOW_RAW_DIR  = DATASET_DIR / "02. Low Light - Raw"

# Output folders
HAZY_OUT_DIR = OUTPUT_DIR / "hazy-student-enhanced"
LOW_OUT_DIR  = OUTPUT_DIR / "lowlight-student-enhanced"


# =============================================================================
#                               Small utilities
# =============================================================================
def clip_uint8(img: np.ndarray) -> np.ndarray:
    """Clip image to [0,255] and return uint8."""
    return np.clip(img, 0, 255).astype(np.uint8)


def limit_saturation(bgr: np.ndarray, sat_scale: float = 0.92) -> np.ndarray:
    """
    Reduce/scale saturation in HSV space.
    Useful to match a softer "GT-like" look (avoid over-saturated output).
    """
    hsv = cv2.cvtColor(bgr, cv2.COLOR_BGR2HSV).astype(np.float32)
    hsv[..., 1] *= sat_scale
    hsv[..., 1] = np.clip(hsv[..., 1], 0, 255)
    return cv2.cvtColor(hsv.astype(np.uint8), cv2.COLOR_HSV2BGR)


# =============================================================================
#               Hazy enhancement (Color Attenuation Prior - CAP)
# =============================================================================
def cap_airlight(bgr: np.ndarray, top_percent: float = 0.001) -> np.ndarray:
    """
    Estimate airlight A (BGR float) from the brightest pixels in grayscale.
    Uses mean of top_percent brightest pixels.
    """
    gray = cv2.cvtColor(bgr, cv2.COLOR_BGR2GRAY).astype(np.float32)
    flat = gray.reshape(-1)

    num = max(1, int(flat.size * top_percent))
    idx = np.argpartition(flat, -num)[-num:] 

    pixels = bgr.reshape(-1, 3).astype(np.float32)
    A = np.mean(pixels[idx], axis=0)
    return A


def cap_depth_map(bgr: np.ndarray) -> np.ndarray:
    """
    CAP depth approximation:
      depth ~ a*V + b*(1 - S) + c
    where:
      - V captures brightness veil
      - S captures attenuation of color
    """
    hsv = cv2.cvtColor(bgr, cv2.COLOR_BGR2HSV).astype(np.float32) / 255.0
    S = hsv[..., 1]
    V = hsv[..., 2]

    a, b, c = 0.8, 0.6, 0.0
    d = a * V + b * (1.0 - S) + c

    # Normalize depth to [0..1]
    d = (d - d.min()) / (d.max() - d.min() + 1e-8)
    return d.astype(np.float32)


def cap_refine_t(gray01: np.ndarray, t: np.ndarray, radius: int = 40, eps: float = 1e-3) -> np.ndarray:
    """
    Refine transmission using guided filter (edge-preserving smoothing).
    If guidedFilter fails, fall back to bilateral filtering on transmission.
    """
    try:
        return xip.guidedFilter(guide=gray01, src=t.astype(np.float32), radius=radius, eps=eps)
    except Exception:
        t8 = clip_uint8(t * 255)
        tbf = cv2.bilateralFilter(t8, d=9, sigmaColor=50, sigmaSpace=50)
        return tbf.astype(np.float32) / 255.0


def enhance_hazy(bgr_img: np.ndarray) -> np.ndarray:
    """
    Dehazing using CAP:
      1) Estimate airlight A
      2) Compute depth map d
      3) Transmission t = exp(-beta * d)
      4) Refine t with guided filter
      5) Recover scene radiance J
      6) Soft LAB adjustments + mild desaturation for GT-like softness
    """
    # 1) Airlight (BGR float)
    A = cap_airlight(bgr_img, top_percent=0.001).astype(np.float32)

    # 2) Depth map
    d = cap_depth_map(bgr_img)

    # 3) Transmission
    beta = 1.25 
    t = np.exp(-beta * d).astype(np.float32)

    # 4) Refine transmission (edge-preserving)
    gray01 = cv2.cvtColor(bgr_img, cv2.COLOR_BGR2GRAY).astype(np.float32) / 255.0
    t = cap_refine_t(gray01, t, radius=50, eps=1e-3)

    # 5) Clamp transmission to avoid division blow-ups
    t0 = 0.14
    t = np.clip(t, t0, 1.0)

    # Recover radiance: J = (I - A)/t + A
    I = bgr_img.astype(np.float32)
    J = (I - A[None, None, :]) / t[..., None] + A[None, None, :]
    J = clip_uint8(J)

    # 6) Gentle color/brightness tuning in LAB
    lab = cv2.cvtColor(J, cv2.COLOR_BGR2LAB)
    L, a_ch, b_ch = cv2.split(lab)

    # Reduce excessive red/warm cast
    a_ch = a_ch.astype(np.float32)
    a_ch = 128 + (a_ch - 128) * 0.90
    a_ch = np.clip(a_ch, 0, 255).astype(np.uint8)

    # Soft lift on L
    L = cv2.convertScaleAbs(L, alpha=1.01, beta=4)

    # Very mild CLAHE for gentle contrast
    clahe = cv2.createCLAHE(clipLimit=0.85, tileGridSize=(8, 8))
    L = clahe.apply(L)

    out = cv2.cvtColor(cv2.merge([L, a_ch, b_ch]), cv2.COLOR_LAB2BGR)

    # Slight desaturation
    out = limit_saturation(out, sat_scale=0.86)
    return out


# =============================================================================
#                 Low-light enhancement (final tuned pipeline)
# =============================================================================
def enhance_lowlight(bgr: np.ndarray) -> np.ndarray:
    """
    Low-light enhancement steps:
      1) Light denoise to reduce noise amplification later
      2) Gamma lift (float) to brighten smoothly
      3) LAB:
         - White-balance by pulling a/b channel means toward 128
         - CLAHE on L + small brightness push
      4) Vignette/illumination correction using a radial gain,
         but scaled down in dark/noisy regions using a luminance mask
      5) Vibrance-like saturation (boost low-sat pixels more than high-sat),
         plus a small V lift to avoid "dead" look
      5.1) Local green suppression to handle shadow green cast/noise
      6) Final bilateral filter to clean remaining speckle
      + Extra shadow-only green suppression pass (stronger, more targeted)
    """
    # 1) Denoise a bit first
    den = cv2.fastNlMeansDenoisingColored(bgr, None, 2, 2, 7, 21)

    # 2) Gamma lift in float (keeps smooth gradients)
    f = den.astype(np.float32) / 255.0
    gamma = 0.42
    f = np.power(np.clip(f, 0, 1), gamma)

    # 3) CLAHE + WB in LAB
    lab = cv2.cvtColor((f * 255).astype(np.uint8), cv2.COLOR_BGR2LAB)
    L, a, b = cv2.split(lab)

    # White-balance: shift mean of a/b toward 128
    a_f = a.astype(np.float32)
    b_f = b.astype(np.float32)
    a_f -= (np.mean(a_f) - 128.0) * 0.7
    b_f -= (np.mean(b_f) - 128.0) * 0.7
    a = np.clip(a_f, 0, 255).astype(np.uint8)
    b = np.clip(b_f, 0, 255).astype(np.uint8)

    # Gentle CLAHE on L + small brightness push
    clahe = cv2.createCLAHE(clipLimit=1.25, tileGridSize=(12, 12))
    L2 = clahe.apply(L)
    L2 = cv2.convertScaleAbs(L2, alpha=1.05, beta=18)

    # Back to BGR (float 0..1 for further safe processing)
    lab2 = cv2.merge([L2, a, b])
    out = cv2.cvtColor(lab2, cv2.COLOR_LAB2BGR).astype(np.float32) / 255.0

    # 4) Vignette correction with radial gain (bounded),
    #    scaled down in dark/noisy areas using luminance mask
    h, w = out.shape[:2]
    yy, xx = np.mgrid[0:h, 0:w].astype(np.float32)
    cx, cy = (w - 1) / 2.0, (h - 1) / 2.0
    r = np.sqrt((xx - cx) ** 2 + (yy - cy) ** 2)
    r = r / (r.max() + 1e-6)

    strength = 0.60
    gain_max = 1.40
    gain = 1.0 + strength * (r ** 2)
    gain = np.clip(gain, 1.0, gain_max)

    lum = out.mean(axis=2) 
    lum_mask = np.clip((lum - 0.15) / 0.60, 0, 1)
    gain = 1.0 + (gain - 1.0) * lum_mask

    out = np.clip(out * gain[..., None], 0, 1)

    # 5) Vibrance + mild value lift
    hsv = cv2.cvtColor((out * 255).astype(np.uint8), cv2.COLOR_BGR2HSV).astype(np.float32)
    s = hsv[..., 1]
    v = hsv[..., 2]

    s_boost = 1.10 + (1.0 - s / 255.0) * 0.30
    s = s * s_boost

    v = v * 1.02 + 2  # small brightness lift to maintain richness

    hsv[..., 1] = np.clip(s, 0, 235)
    hsv[..., 2] = np.clip(v, 0, 255)

    out_u8 = cv2.cvtColor(hsv.astype(np.uint8), cv2.COLOR_HSV2BGR)

    # 5.1) Local green cast suppression (targets left greenish shadows)
    bch, gch, rch = cv2.split(out_u8.astype(np.float32))

    dark = (0.2126 * rch + 0.7152 * gch + 0.0722 * bch) < 160
    greenish = (gch > rch * 1.18) & (gch > bch * 1.18) & dark

    mask = greenish.astype(np.float32)
    mask = cv2.GaussianBlur(mask, (0, 0), sigmaX=11, sigmaY=11)

    gch = gch * (1.0 - 0.20 * mask)

    out_u8 = cv2.merge([
        np.clip(bch, 0, 255).astype(np.uint8),
        np.clip(gch, 0, 255).astype(np.uint8),
        np.clip(rch, 0, 255).astype(np.uint8),
    ])

    # 6) Final light denoise
    out_u8 = cv2.bilateralFilter(out_u8, d=7, sigmaColor=30, sigmaSpace=30)

    # Extra shadow-only green suppression (stronger, more targeted)
    bch, gch, rch = cv2.split(out_u8.astype(np.float32))

    Y = 0.2126 * rch + 0.7152 * gch + 0.0722 * bch
    excess = gch - 0.5 * (rch + bch)

    mask = ((Y < 170) & (excess > 12)).astype(np.float32)
    mask = cv2.GaussianBlur(mask, (0, 0), sigmaX=15, sigmaY=15)

    gch = gch * (1.0 - 0.28 * mask)
    rch = rch * (1.0 + 0.06 * mask)

    out_u8 = cv2.merge([
        np.clip(bch, 0, 255).astype(np.uint8),
        np.clip(gch, 0, 255).astype(np.uint8),
        np.clip(rch, 0, 255).astype(np.uint8),
    ])

    return out_u8


# =============================================================================
#                               Batch processing
# =============================================================================
def process_folder(input_dir: Path, output_dir: Path, enhance_fn):
    """
    Read all images in input_dir, enhance each using enhance_fn, and save to output_dir.
    """
    output_dir.mkdir(parents=True, exist_ok=True)

    image_exts = {".png", ".jpg", ".jpeg", ".bmp", ".tif", ".tiff"}
    files = sorted([p for p in input_dir.iterdir() if p.suffix.lower() in image_exts])

    if not files:
        raise FileNotFoundError(f"No images found in: {input_dir}")

    for img_path in files:
        img = cv2.imread(str(img_path))
        if img is None:
            print(f"[WARN] Could not read: {img_path.name}")
            continue

        enhanced = enhance_fn(img)

        out_path = output_dir / img_path.name
        cv2.imwrite(str(out_path), enhanced)

    print(f"[OK] Processed {len(files)} images from {input_dir.name} -> {output_dir.name}")


def main():
    # Sanity checks
    if not HAZY_RAW_DIR.exists():
        raise FileNotFoundError(f"Missing folder: {HAZY_RAW_DIR}")
    if not LOW_RAW_DIR.exists():
        raise FileNotFoundError(f"Missing folder: {LOW_RAW_DIR}")

    # Process both tasks
    process_folder(HAZY_RAW_DIR, HAZY_OUT_DIR, enhance_hazy)
    process_folder(LOW_RAW_DIR, LOW_OUT_DIR, enhance_lowlight)


if __name__ == "__main__":
    main()
