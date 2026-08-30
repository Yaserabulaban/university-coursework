import csv
import sys
import os
import re

# Reads only the selected range of rows from the CSV dataset
# Returns a list of (int, string) tuples
def read_rows(filename, start_row, end_row):
    with open(filename, 'r') as file:
        reader = csv.reader(file)
        return [(int(row[0]), row[1]) for i, row in enumerate(reader) if start_row <= i + 1 <= end_row]

# Formats the array to a readable string format: [123/name, 456/xyz]
def format_array(arr):
    return "[" + ", ".join(f"{num}/{txt}" for num, txt in arr) + "]"

# Recursive Quick Sort with step logging
def quick_sort_with_steps(arr, low, high, steps):
    if low < high:
        pi = partition(arr, low, high, steps)  # Perform partition
        steps.append(f"pi={pi} " + format_array(arr))  # Record array state after partition
        quick_sort_with_steps(arr, low, pi - 1, steps)  # Sort left subarray
        quick_sort_with_steps(arr, pi + 1, high, steps)  # Sort right subarray

# Partitions the array using last element as pivot
# Rearranges elements and returns the pivot index
def partition(arr, low, high, steps):
    pivot = arr[high][0]  # Use the integer part for comparison
    i = low - 1
    for j in range(low, high):
        if arr[j][0] <= pivot:
            i += 1
            arr[i], arr[j] = arr[j], arr[i]  # Swap
    arr[i+1], arr[high] = arr[high], arr[i+1]  # Place pivot in correct position
    return i + 1  # Return pivot index

def main():
    # Check if correct number of arguments were provided
    if len(sys.argv) != 4:
        print("Usage: python quick_sort_step.py <filename> <start_row> <end_row>")
        return

    # Parse command line arguments
    filename = sys.argv[1]
    start_row = int(sys.argv[2])
    end_row = int(sys.argv[3]) 

    # Output file named based on row range
    output_file = f"quick_sort_step_{start_row}_{end_row}.txt"

    # Load data from selected row range
    data = read_rows(filename, start_row, end_row)
    steps = [format_array(data)]  # Initial unsorted array

    # Perform quick sort and log steps
    quick_sort_with_steps(data, 0, len(data) - 1, steps)

    # Write steps to output file
    with open(output_file, 'w') as f:
        for step in steps:
            f.write(step + "\n")

    print(f"Steps written to {output_file}")

# Entry point
if __name__ == '__main__':
    main()
