import csv
import time
import random

def read_dataset(filename):
    with open(filename, 'r') as file:
        reader = csv.reader(file)
        return [(int(row[0]), row[1]) for row in reader]

def binary_search(arr, target):
    low, high = 0, len(arr) - 1
    while low <= high:
        mid = (low + high) // 2
        if arr[mid][0] == target:
            return mid
        elif arr[mid][0] < target:
            low = mid + 1
        else:
            high = mid - 1
    return -1

def measure_search_time(arr, target, trials):
    start = time.time()
    for _ in range(trials):
        binary_search(arr, target)
    end = time.time()
    return end - start

def main():
    input_file = 'dataset_sample.csv'
    output_file = 'binary_search_result.txt'

    data = read_dataset(input_file)
    size = len(data)
    trials = size

    first = data[0][0]
    middle = data[size // 2][0]
    worst = 2_000_000_000  # guaranteed not in dataset

    t_best = measure_search_time(data, first, trials)
    t_avg = measure_search_time(data, middle, trials)
    t_worst = measure_search_time(data, worst, trials)

    with open(output_file, 'w') as f:
        f.write(f"Best case (target={first}): {t_best:.6f} sec for {trials} searches\n")
        f.write(f"Average case (target={middle}): {t_avg:.6f} sec for {trials} searches\n")
        f.write(f"Worst case (target={worst}): {t_worst:.6f} sec for {trials} searches\n")

    print(f"Results written to {output_file}")

if __name__ == '__main__':
    main()
