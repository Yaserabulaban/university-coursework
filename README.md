# University coursework

Coursework from my BSc Computer Science (Data Science) at Multimedia University,
Cyberjaya — July 2023 to July 2026, First Class Honours, CGPA 3.91.

One folder per project, newest year first. Datasets are included wherever they are small
enough to be useful; demo videos, reports and assignment briefs are not. Where a dataset was
too large to commit, the notes below say where to get it.

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

### `year-3/image-enhancement`
Haze removal and low-light enhancement without any pretrained model. Colour Attenuation Prior
dehazing at 19.02 dB PSNR / 0.817 SSIM; a seven-stage low-light pipeline at 17.23 dB / 0.715. Solo.
Stack: OpenCV, numpy, guided filter.

```
src/enhancement.py          the two pipelines
src/evaluate_metrics.py     PSNR and SSIM scoring
src/histogram-analysis.ipynb
dataset/                    hazy and low-light inputs with ground truth
figures/histograms/         histogram comparisons per stage
```

Enhanced outputs are not committed — regenerate them by running `src/enhancement.py`
against `dataset/`.

### `year-3/amazon-prime-association-rules`
Four research questions over 2,530 subscribers, with chi-square tests used to check whether the
mined rules meant anything. Mostly they did not — lift sat near 1.0, and the write-up says so.
Stack: pandas, mlxtend Apriori, SciPy.

```
association-rules.ipynb
data/amazon-prime-users.csv
```

### `year-3/telco-plan-analysis`
31 Malaysian prepaid plans collected by hand from five providers, with advertised "unlimited"
offers normalised to real GB using fair-use caps so cost-per-GB could be compared honestly.
Stack: Power BI, Excel.

```
data/plans-raw.xlsx         as collected
data/plans-cleaned.xlsx     normalised, with derived cost-per-GB
```

The Power BI report file itself is not committed; the cleaned workbook is the input it reads.
Plan pages were collected by hand from five providers' published tariffs.

## Year 2

### `year-2/airbnb-property-classification`
Multiclass property-type prediction on Boston Airbnb data. A DNN reached 0.89 accuracy and 0.91
macro-F1, beating a logistic regression that scored *higher* accuracy (0.77) but collapsed to
0.16 macro-F1 by predicting the majority class for almost everything.
Stack: PyTorch, scikit-learn, SMOTE, TF-IDF.

```
airbnb-property-classification.ipynb
data/listings.csv           the table the model trains on
data/selected-features.csv  the reduced feature set
```

`calendar.csv` and `reviews.csv` are too large to commit — the full set is at
[Inside Airbnb](http://insideairbnb.com/get-the-data).

### `year-2/african-financial-crises`
Predicting systemic banking crises across 13 African countries, 1870–2013. 0.99 accuracy at a
0.30 decision threshold, recall 1.00 on 17 crisis cases.
Stack: pandas, scikit-learn, Random Forest.

```
analysis.ipynb
data/african-crises.csv
```

### `year-2/kwazam-chess`
A 5×8 board chess variant with Swing GUI under enforced MVC separation, eight design patterns
mapped class by class, and pieces that swap type every two turns. **Built individually.**
Stack: Java, Swing, AWT.

```
src/KwazamChess.java        entry point
src/model/                  board, pieces, game state, sound
src/view/                   main window, board view, menu bar
src/controller/             game controller, input handler
docs/uml/                   class diagram
docs/use-cases/             one diagram per use case
images/                     piece sprites
```

Compile and run with `javac -d out $(find src -name '*.java') && java -cp out KwazamChess`.

### `year-2/cpu-scheduling-simulator`
Round robin, shortest remaining time, shortest job next and non-preemptive priority behind one
abstract base class, with rendered Gantt charts and per-process turnaround and waiting times.
Stack: Java.

```
src/SchedulingAlgorithm.java   the abstract base
src/RoundRobin.java  src/ShortestRemainingTime.java
src/ShortestJobNext.java  src/NonPrePriority.java
src/Process.java  src/Main.java
```

### `year-2/petrol-delivery-system`
On-demand fuel delivery with three roles — customer, vendor, driver. 8-table schema,
15 migrations, 27 templates. I owned the vendor subsystem and the data dictionary.
Stack: Django, SQLite, Bootstrap.

```
analysis/                   ERD, use-case diagram, sequence diagrams per role
design/                     component, state and refined sequence diagrams
src/                        the Django project
```

### `year-2/sorting-benchmark`
Merge sort vs quick sort implemented from scratch and timed across ten input sizes from 1,000 to
25,000,000 elements. Quick sort won at every size — 276.9 s vs 341.8 s at 25M. Binary search
profiled across four cases.
Stack: Python, Java (data generator).

```
src/merge_sort.py  src/quick_sort.py
src/binary_search.py  src/binary_search_alt.py
src/dataset_generator.java
traces/                     step-by-step instrumented versions used for the write-up
notes/                      implementation and trace notes
timing-results.xlsx         the measured timings
```

The generated input CSVs (~1.4 GB) are not committed — regenerate them with
`src/dataset_generator.java`.

### `year-2/r-statistical-analysis`
Two solo assignments. Pearson r = 0.818 derived by hand from sums of squares; a one-sample
t-test at t = −31.67 (p ≈ 5.7e−153); one-way ANOVA F = 126.4 on a product launch.
Stack: R, ggplot2, base stats.

```
correlation-study/students-performance.csv
battery-life-and-anova/battery-life.csv
battery-life-and-anova/fresh-fizz-sales.csv
battery-life-and-anova/session-history.R
```

`session-history.R` is the R console history rather than a cleaned script — it includes the
false starts as well as the commands that produced the reported figures.

## Year 1

### `year-1/robot-war-simulator`
Turn-based battlefield simulator: four capability mixins composing into seven robot types over
virtual inheritance, with a linked list and respawn queue written by hand rather than pulled
from the STL.
Stack: C++.

```
simulator/Main.cpp
simulator/include/           16 headers — robots, battlefield, list, queue
simulator/src/               16 implementations
simulator/robots.txt         the input roster
simulator/simulation-log.txt a sample run
```

Build with `g++ -std=c++17 -Isimulator/include -o robotwar simulator/Main.cpp simulator/src/*.cpp`.

### `year-1/assembly-vm-interpreter`
A virtual machine with 7 registers, 4 status flags, 64 bytes of addressable memory and an
18-instruction set including rotates, shifts and register-indirect addressing.
Stack: C++ (standard library only).

```
virtual-machine.cpp
```

### `year-1/carwash-queue-simulator`
Discrete-event simulation of a three-slot car wash, driven by two random number generators
written from scratch — a linear congruential generator and a uniform random variate generator.
Stack: MATLAB-syntax `.m` on FreeMat.

```
src/main.m                          the simulation driver
src/generateLCGRandomNumbers.m      linear congruential generator
src/generateRVGRandomNumbers.m      uniform random variate generator
src/simulateCars.m  src/evaluateResults.m  and the table/printing helpers
```

### `year-1/car-rental-database`
Payment subsystem for a car rental company: 11 tables normalised to 3NF, with the normalisation
proved table by table.
Stack: SQL, IBM DB2.

```
schema.sql                  tables, keys and constraints
payment-subsystem.sql       views, triggers and the trigger functions
```

### `year-1/arm-assembly-counter`
ARM assembly for the VisUAL emulator, plus a synchronous counter designed from a state
transition diagram, D-flip-flop excitation table and five-variable K-maps.
Stack: ARM assembly, Logisim.

```
arm-assembly/part-a.s  arm-assembly/part-b.s
counter/synchronous-counter.cv
```

---

## Notes

Where a project was built alone that is stated above; everything else was group work, and the
folders hold my own contribution plus the shared artefacts. Deliberately excluded from this
repository:

- **Demo videos, reports and assignment briefs** — the code and data are here, the paperwork is not.
- **Generated benchmark data** in `year-2/sorting-benchmark` (~1.4 GB of CSVs).
- **The two large secondary Airbnb tables** (`calendar.csv`, `reviews.csv`).
- **Enhancement outputs** in `year-3/image-enhancement/output/`.
