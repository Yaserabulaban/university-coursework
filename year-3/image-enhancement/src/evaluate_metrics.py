import cv2
import numpy as np
from pathlib import Path

# SSIM requires scikit-image
try:
    from skimage.metrics import structural_similarity as ssim
except Exception as e:
    raise ImportError(
        "scikit-image is required for SSIM.\n"
        "Install it with: pip install scikit-image\n"
        f"Original error: {e}"
    )

# =============================================================================
#                       Paths (match project structure)
# =============================================================================
PROJECT_ROOT = Path(__file__).resolve().parents[1]

# Find dataset folder (name must = "dataset")
DATASET_DIR = None
for name in ["dataset"]:
    candidate = PROJECT_ROOT / name
    if candidate.exists():
        DATASET_DIR = candidate
        break

if DATASET_DIR is None:
    raise FileNotFoundError(f"Dataset folder not found under: {PROJECT_ROOT}")

OUTPUT_DIR = PROJECT_ROOT / "output"

# Ground Truth (GT) folders inside dataset
HAZY_GT_DIR = DATASET_DIR / "01. Hazy - Enhanced (GT)"
LOW_GT_DIR  = DATASET_DIR / "02. Low Light - Enhanced (GT)"

# Student output folders inside output/
HAZY_STU_DIR = OUTPUT_DIR / "hazy-student-enhanced"
LOW_STU_DIR  = OUTPUT_DIR / "lowlight-student-enhanced"


# =============================================================================
#                               Metric helpers
# =============================================================================
def read_gray(path: Path) -> np.ndarray:
    """
    Read an image from disk and return its grayscale version.

    Notes:
    - OpenCV loads images as BGR.
    - Metrics here are computed on grayscale to keep evaluation consistent.
    """
    img = cv2.imread(str(path))
    if img is None:
        raise FileNotFoundError(f"Could not read image: {path}")
    return cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)


def psnr_cv(ref_gray: np.ndarray, test_gray: np.ndarray) -> float:
    """
    Compute PSNR using OpenCV (expects images are same size/type).
    """
    return float(cv2.PSNR(ref_gray, test_gray))


def ssim_gray(ref_gray: np.ndarray, test_gray: np.ndarray) -> float:
    """
    Compute SSIM on grayscale images.
    data_range=255 because grayscale images are uint8 (0..255).
    """
    return float(ssim(ref_gray, test_gray, data_range=255))


def sharpness_var_laplacian(gray: np.ndarray) -> float:
    """
    Simple sharpness metric: variance of Laplacian response.
    Higher = more high-frequency content (often sharper, but can be noise too).
    """
    lap = cv2.Laplacian(gray, cv2.CV_64F)
    return float(lap.var())


def contrast_std(gray: np.ndarray) -> float:
    """
    Simple contrast metric: standard deviation of intensities.
    Higher std often means higher global contrast.
    """
    return float(np.std(gray))


# =============================================================================
#                               Folder evaluation
# =============================================================================
def eval_folder(gt_dir: Path, stu_dir: Path, label: str):
    """
    Evaluate all GT images in gt_dir against student images in stu_dir
    (matched by filename). Prints per-image metrics and an average row.

    Metrics computed:
    - PSNR (student vs GT, grayscale)
    - SSIM (student vs GT, grayscale)
    - Sharpness (GT and student separately)
    - Contrast (GT and student separately)
    """
    exts = {".png"}

    if not gt_dir.exists():
        raise FileNotFoundError(f"{label}: GT folder not found: {gt_dir}")
    if not stu_dir.exists():
        raise FileNotFoundError(f"{label}: Student output folder not found: {stu_dir}")

    gt_files = sorted([p for p in gt_dir.iterdir() if p.suffix.lower() in exts])
    if not gt_files:
        raise FileNotFoundError(f"{label}: No images found in GT folder: {gt_dir}")

    rows = []
    missing = 0

    for gt_path in gt_files:
        stu_path = stu_dir / gt_path.name

        # Skip if student output does not exist (filename mismatch or not generated)
        if not stu_path.exists():
            missing += 1
            continue

        # Read grayscale GT and Student
        gt_gray = read_gray(gt_path)
        st_gray = read_gray(stu_path)

        # Ensure same resolution before metrics
        if gt_gray.shape != st_gray.shape:
            st_gray = cv2.resize(
                st_gray,
                (gt_gray.shape[1], gt_gray.shape[0]),
                interpolation=cv2.INTER_AREA
            )

        rows.append({
            "image": gt_path.name,
            "psnr": psnr_cv(gt_gray, st_gray),
            "ssim": ssim_gray(gt_gray, st_gray),
            "sharp_gt": sharpness_var_laplacian(gt_gray),
            "sharp_student": sharpness_var_laplacian(st_gray),
            "contrast_gt": contrast_std(gt_gray),
            "contrast_student": contrast_std(st_gray),
        })

    if missing > 0:
        print(f"[WARN] {label}: {missing} student files missing (filename mismatch or not generated).")

    if not rows:
        raise RuntimeError(
            f"{label}: No matching image pairs found. "
            f"Check that student outputs exist and filenames match GT exactly."
        )

    # print results
    print("\n" + "=" * 80)
    print(f"{label} METRICS (Student vs GT)")
    print("=" * 80)

    header = (
        f"{'Image':<14}  {'PSNR':>7}  {'SSIM':>7}  "
        f"{'Sharp(GT)':>10}  {'Sharp(STU)':>11}  "
        f"{'Contr(GT)':>10}  {'Contr(STU)':>11}"
    )
    print(header)
    print("-" * len(header))

    for r in rows:
        print(
            f"{r['image']:<14}  {r['psnr']:7.2f}  {r['ssim']:7.3f}  "
            f"{r['sharp_gt']:10.2f}  {r['sharp_student']:11.2f}  "
            f"{r['contrast_gt']:10.2f}  {r['contrast_student']:11.2f}"
        )

    # Compute average for numeric columns
    avg = {
        k: float(np.mean([r[k] for r in rows]))
        for k in rows[0].keys()
        if k != "image"
    }

    print("-" * len(header))
    print(
        f"{'AVERAGE':<14}  {avg['psnr']:7.2f}  {avg['ssim']:7.3f}  "
        f"{avg['sharp_gt']:10.2f}  {avg['sharp_student']:11.2f}  "
        f"{avg['contrast_gt']:10.2f}  {avg['contrast_student']:11.2f}"
    )

    return rows, avg


def main():
    """
    Runs evaluation for:
    1) Hazy: student vs GT
    2) Low-light: student vs GT
    """
    eval_folder(HAZY_GT_DIR, HAZY_STU_DIR, "HAZY")
    eval_folder(LOW_GT_DIR, LOW_STU_DIR, "LOW-LIGHT")


if __name__ == "__main__":
    main()
