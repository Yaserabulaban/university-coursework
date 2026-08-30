===================================================
quick_sort_step.py
===================================================

This script performs Quick Sort on a specific portion of a CSV dataset 
and logs every step of the sorting process to a text file.

---------------------------------------------------
File name: quick_sort_step.py
---------------------------------------------------
This script accepts:
1. A dataset CSV file (e.g., dataset_1,000_sample.csv)
2. A start row number
3. An end row number

Each row in the dataset must be in this format:
    integer,string
Example:
    1981761604,uoren

---------------------------------------------------
How to Run
---------------------------------------------------

In terminal or command prompt, run the script with 3 arguments:

> python quick_sort_step.py <input_csv> <start_row> <end_row>

Example:
> python quick_sort_step.py dataset_1,000_sample.csv 1 7

This will:
- Read lines 1 to 7 from the CSV
- Sort them using Quick Sort
- Save the step-by-step output to:
  quick_sort_step_1,000_1_7.txt

---------------------------------------------------
Output Format
---------------------------------------------------

The output text file logs the sorting process, e.g.:

[1981761604/uoren, 56205740/igerk, ...]
pi=4 [56205740/igerk, ..., 1869583452/gslagi]
...

===================================================
Author: Yaser Abulaban
CCP6214 Algorithm Design and Analysis – 2025
===================================================
