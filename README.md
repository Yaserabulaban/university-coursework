# University projects

Coursework from my BSc Computer Science (Data Science) at Multimedia University,
Cyberjaya — July 2023 to July 2026, First Class Honours, CGPA 3.91.

One folder per project, newest year first. Datasets are included wherever they are small
enough to be useful; demo videos, reports and assignment briefs are not. Where a dataset was
too large to commit, the project's own notes say where to get it.

The six projects I consider my strongest have their own repositories rather than living here:

| Project | Repository |
|---|---|
| ParkViewRT — vision-based parking occupancy (final year project) | [`parkviewrt`](https://github.com/Yaserabulaban/parkviewrt) |
| FIFA 23 Steam review sentiment | [`fifa23-review-sentiment`](https://github.com/Yaserabulaban/fifa23-review-sentiment) |
| Global STI Trends dashboard | [`sti-trends-dashboard`](https://github.com/Yaserabulaban/sti-trends-dashboard) |
| Cartly — recipe-to-cart marketplace | [`Cartly-Recipe-to-Cart-Marketplace`](https://github.com/Yaserabulaban/Cartly-Recipe-to-Cart-Marketplace) |
| Insurance fraud detection | [`insurance-fraud-detection`](https://github.com/Yaserabulaban/insurance-fraud-detection) |
| FER preprocessing ablation study | [`fer-preprocessing-study`](https://github.com/Yaserabulaban/fer-preprocessing-study) |

Write-ups for all six: **https://Yaserabulaban.github.io**

---

## Year 3

| Folder | What it is | Stack |
|---|---|---|
| `year-3/image-enhancement` | Haze removal and low-light enhancement without any pretrained model. Colour Attenuation Prior dehazing at 19.02 dB PSNR / 0.817 SSIM; a seven-stage low-light pipeline at 17.23 dB / 0.715. Solo. | OpenCV, numpy, guided filter |
| `year-3/rocky-linux-server` | Enterprise Linux build: 50 accounts across 5 department groups, ACL-based access control, key-only SSH with root login disabled. Solo. | Rocky Linux 9.7, Apache, Samba, firewalld, SELinux |
| `year-3/amazon-prime-association-rules` | Four research questions over 2,530 subscribers, with chi-square tests used to check whether the mined rules meant anything. Mostly they did not — lift sat near 1.0, and the write-up says so. | pandas, mlxtend Apriori, SciPy |
| `year-3/telco-plan-analysis` | 31 Malaysian prepaid plans collected by hand from five providers, with advertised "unlimited" offers normalised to real GB using fair-use caps so cost-per-GB could be compared honestly. | Power BI, Excel |

## Year 2

| Folder | What it is | Stack |
|---|---|---|
| `year-2/airbnb-property-classification` | Multiclass property-type prediction on Boston Airbnb data. A DNN reached 0.89 accuracy and 0.91 macro-F1, beating a logistic regression that scored *higher* accuracy (0.77) but collapsed to 0.16 macro-F1 by predicting the majority class for almost everything. | PyTorch, scikit-learn, SMOTE, TF-IDF |
| `year-2/african-financial-crises` | Predicting systemic banking crises across 13 African countries, 1870–2013. 0.99 accuracy at a 0.30 decision threshold, recall 1.00 on 17 crisis cases. | pandas, scikit-learn, Random Forest |
| `year-2/r-statistical-analysis` | Two solo assignments. Pearson r = 0.818 derived by hand from sums of squares; a one-sample t-test at t = −31.67 (p ≈ 5.7e−153); one-way ANOVA F = 126.4 on a product launch. | R, ggplot2, base stats |
| `year-2/sorting-benchmark` | Merge sort vs quick sort implemented from scratch and timed across ten input sizes from 1,000 to 25,000,000 elements. Quick sort won at every size — 276.9 s vs 341.8 s at 25M. Binary search profiled across four cases. | Python, Java (data generator) |
| `year-2/kwazam-chess` | A 5×8 board chess variant with Swing GUI under enforced MVC separation, eight design patterns mapped class by class, and pieces that swap type every two turns. **Built individually.** | Java, Swing, AWT |
| `year-2/cpu-scheduling-simulator` | Round robin, shortest remaining time, shortest job next and non-preemptive priority behind one abstract base class, with rendered Gantt charts and per-process turnaround and waiting times. | Java |
| `year-2/petrol-delivery-system` | On-demand fuel delivery with three roles — customer, vendor, driver. 8-table schema, 15 migrations, 27 templates. I owned the vendor subsystem and the data dictionary. | Django, SQLite, Bootstrap |
| `year-2/ehr-blockchain-proposal` | A nine-page LaTeX research proposal for dynamic patient consent in electronic health records, with gap analysis over six peer-reviewed papers. | LaTeX, BibTeX |

## Year 1

| Folder | What it is | Stack |
|---|---|---|
| `year-1/robot-war-simulator` | Turn-based battlefield simulator: four capability mixins composing into seven robot types over virtual inheritance, with a linked list and respawn queue written by hand rather than pulled from the STL. | C++ |
| `year-1/assembly-vm-interpreter` | A virtual machine with 7 registers, 4 status flags, 64 bytes of addressable memory and an 18-instruction set including rotates, shifts and register-indirect addressing. | C++ (standard library only) |
| `year-1/carwash-queue-simulator` | Discrete-event simulation of a three-bay car wash, driven by two random number generators written from scratch — a linear congruential generator and a uniform random variate generator. | MATLAB-syntax `.m` on FreeMat |
| `year-1/car-rental-database` | Payment subsystem for a car rental company: 11 tables normalised to 3NF, with the normalisation proved table by table. | SQL, IBM DB2 |
| `year-1/arm-assembly-counter` | ARM assembly for the VisUAL emulator, plus a synchronous counter designed from a state transition diagram, D-flip-flop excitation table and five-variable K-maps. | ARM assembly, Logisim |

---

## Notes

Group work is marked as such in each project's own files; where a project was built alone
that is stated above. A few things are deliberately excluded from this repository:

- **Demo videos, reports and assignment briefs** — the code and data are here, the paperwork is not.
- **Generated benchmark data** in `year-2/sorting-benchmark` (~1.4 GB of CSVs) — regenerate it
  with the scripts in that folder.
- **The two large secondary Airbnb tables** (`calendar.csv`, `reviews.csv`) — `listings.csv`,
  the file the model actually trains on, is committed. The full set is at
  [Inside Airbnb](http://insideairbnb.com/get-the-data).
- **Enhancement outputs** in `year-3/image-enhancement/output/` — reproducible from `src/`
  against the sample inputs in `dataset/`.
