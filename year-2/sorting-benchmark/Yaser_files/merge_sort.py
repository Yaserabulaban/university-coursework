import csv
import time

# Reads a CSV file and returns a list of (int, string) tuples
def read_dataset(filename):
    with open(filename, 'r') as file:
        reader = csv.reader(file)
        return [(int(row[0]), row[1]) for row in reader]

# Writes a list of (int, string) tuples to a CSV file
def write_dataset(filename, data):
    with open(filename, 'w', newline='') as file:
        writer = csv.writer(file)
        writer.writerows(data)

# Recursive implementation of Merge Sort
def merge_sort(arr):
    if len(arr) <= 1:
        return arr  # Base case: already sorted
    mid = len(arr) // 2
    left = merge_sort(arr[:mid])   # Recursively sort left half
    right = merge_sort(arr[mid:])  # Recursively sort right half
    return merge(left, right)      # Merge the two sorted halves

# Merges two sorted arrays into one sorted array
def merge(left, right):
    result = []
    i = j = 0
    # Compare elements from both halves and merge in sorted order
    while i < len(left) and j < len(right):
        if left[i][0] <= right[j][0]:  # Compare based on integer values
            result.append(left[i])
            i += 1
        else:
            result.append(right[j])
            j += 1
    # Append remaining elements from left or right
    result.extend(left[i:])
    result.extend(right[j:])
    return result

def main():
    # Ask user for input CSV file (e.g., dataset_100000.csv)
    input_filename = input("Please enter the file name: ")
    
    # Extract the size part (e.g., 100000 from dataset_100000.csv)
    size_part = input_filename.split('_')[1]
    output_filename = f'merge_sort_{size_part}.csv'  # Name output file accordingly

    # Read data from input file
    data = read_dataset(input_filename)

    # Start the timer before sorting
    start_time = time.time()
    sorted_data = merge_sort(data)  # Perform Merge Sort
    end_time = time.time()          # End the timer after sorting

    # Write sorted data to output file
    write_dataset(output_filename, sorted_data)

    # Display the sorting time
    print(f"Running time (Merge Sort): {end_time - start_time:.4f} seconds")

# Entry point of the program
if __name__ == '__main__':
    main()
