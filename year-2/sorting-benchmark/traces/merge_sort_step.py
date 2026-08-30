import csv
import sys

def read_rows(filename, start_row, end_row):
    with open(filename, 'r') as file:
        reader = csv.reader(file)
        return [(int(row[0]), row[1]) for i, row in enumerate(reader) if start_row <= i + 1 <= end_row]

def format_array(arr):
    return "[" + ", ".join(f"{x[0]}/{x[1]}" for x in arr) + "]"

def merge_sort_with_steps(arr, steps):
    if len(arr) <= 1:
        return arr
    mid = len(arr) // 2
    left = merge_sort_with_steps(arr[:mid], steps)
    right = merge_sort_with_steps(arr[mid:], steps)
    merged = merge(left, right)
    steps.append(format_array(merged))
    return merged

def merge(left, right):
    result = []
    i = j = 0
    while i < len(left) and j < len(right):
        if left[i][0] <= right[j][0]:
            result.append(left[i])
            i += 1
        else:
            result.append(right[j])
            j += 1
    result.extend(left[i:])
    result.extend(right[j:])
    return result

def main():
    if len(sys.argv) != 4:
        print("Usage: python merge_sort_step.py <filename> <start_row> <end_row>")
        return

    filename = sys.argv[1]
    start_row = int(sys.argv[2])
    end_row = int(sys.argv[3])
    output_file = f"merge_sort_step_{start_row}_{end_row}.txt"

    data = read_rows(filename, start_row, end_row)
    steps = [format_array(data)]

    merge_sort_with_steps(data, steps)

    with open(output_file, 'w') as f:
        for step in steps:
            f.write(step + "\n")

    print(f"Steps written to {output_file}")

if __name__ == '__main__':
    main()
