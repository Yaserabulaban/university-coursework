import csv
import sys

def read_dataset(filename):
    with open(filename, 'r') as file:
        reader = csv.reader(file)
        return [(int(row[0]), row[1]) for row in reader]

def binary_search_trace(data, target):
    trace = []
    low, high = 0, len(data) - 1
    while low <= high:
        mid = (low + high) // 2
        value, word = data[mid]
        trace.append(f"{mid}: {value}/{word}")
        if value == target:
            return trace
        elif value < target:
            low = mid + 1
        else:
            high = mid - 1
    trace.append("-1")
    return trace

def main():
    if len(sys.argv) != 3:
        print("Usage: python binary_search_step.py <filename> <target>")
        return

    filename = sys.argv[1]
    target = int(sys.argv[2])
    output_file = f"binary_search_step_{target}.txt"

    data = read_dataset(filename)
    trace = binary_search_trace(data, target)

    with open(output_file, 'w') as f:
        for line in trace:
            f.write(line + "\n")

    print(f"Search trace written to {output_file}")

if __name__ == '__main__':
    main()
