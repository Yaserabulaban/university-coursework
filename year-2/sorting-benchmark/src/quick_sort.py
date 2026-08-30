import csv
import time

# Reads the CSV dataset and returns a list of (int, string) pairs
def read_dataset(filename):
    with open(filename, 'r') as file:
        reader = csv.reader(file)
        data = [(int(row[0]), row[1]) for row in reader]  # O(n) - reads n elements
        return data

# Writes the sorted data to a CSV file
def write_dataset(filename, data):
    with open(filename, 'w', newline='') as file:
        writer = csv.writer(file)
        writer.writerows(data)  # O(n) - writes n elements

# Recursive implementation of Quick Sort
# Time Complexity:
# Best & Average Case: O(n log n) — if pivot splits array evenly
# Worst Case: O(n²) — if pivot is smallest/largest (e.g., already sorted)
def quick_sort(arr):
    if len(arr) <= 1:
        return arr  # Base case: single or empty array is already sorted — O(1)
    
    pivot = arr[-1]  # Pick the last element as pivot — O(1)

    # Partition the array (excluding pivot)
    # Time: O(n) — one full pass to build left and right
    left = [x for x in arr[:-1] if x[0] <= pivot[0]]   # Elements <= pivot
    right = [x for x in arr[:-1] if x[0] > pivot[0]]   # Elements > pivot

    # Recursively sort both sides and combine — total O(n log n) for balanced split
    return quick_sort(left) + [pivot] + quick_sort(right)

def main():
    # Ask user for file name (e.g., dataset_100000.csv)
    input_filename = input("Please enter the file name: ")

    try:
        # Extract dataset size part to customize output file name
        size_part = input_filename.split('_')[1]
        output_filename = f'quick_sort_{size_part}.csv'
    except IndexError:
        output_filename = 'quick_sort_result.csv'

    # Read the dataset — O(n)
    data = read_dataset(input_filename)

    # Start timer (excluded from complexity)
    start_time = time.time()

    # Perform Quick Sort — expected O(n log n)
    sorted_data = quick_sort(data)

    # Stop timer
    end_time = time.time()

    # Write sorted results — O(n)
    write_dataset(output_filename, sorted_data)

    # Print runtime (not part of complexity)
    print(f"Running time (Quick Sort): {end_time - start_time:.4f} seconds")

# Entry point
if __name__ == '__main__':
    main()
