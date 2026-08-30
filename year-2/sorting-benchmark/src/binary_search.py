import csv
import sys
import time
import random

def read_dataset(filename):
    with open(filename, 'r') as file:
        reader = csv.reader(file)
        return [(int(row[0]), row[1]) for row in reader]

def binary_search(arr, target):
    left, right = 0, len(arr) - 1
    while left <= right:
        mid = (left + right) // 2
        if arr[mid][0] == target:
            return mid
        elif arr[mid][0] < target:
            left = mid + 1
        else:
            right = mid - 1
    return -1

def measure_search_time(arr, target, trials):
    start = time.time()
    for _ in range(trials):
        binary_search(arr, target)
    end = time.time()
    total_time = end - start
    return (total_time / trials)

def main():
    if len(sys.argv) == 2:
        input_file = sys.argv[1]
    else:
        input_file = input("Enter the dataset to read from: ")
    data = read_dataset(input_file)
    size = len(data)
    trials = size
    output_file = f'binary_search_{trials}.txt'

    best = data[(size - 1) // 2][0]
    worst1 = data[-1][0]
    worst2 = 2_000_000_000_000_000  # guaranteed not in dataset

    # t_best = measure_search_time(data, best, trials)
    # t_avg = measure_search_time(data, average, trials)
    # t_worst = measure_search_time(data, worst, trials)

    # Best-case: target in the middle (low steps)
    t_best = measure_search_time(data, best, trials)

    # Average-case: search for random elements from the dataset
    random_target = random.choice(data)[0]
    t_avg = measure_search_time(data, random_target, trials)

    # Worst-case 1: target is first or last element
    t_worst1 = measure_search_time(data, worst1, trials)

    # Worst-case 2: target definitely not in dataset
    t_worst2 = measure_search_time(data, worst2, trials)

    

    with open(output_file, 'w') as f:
        label_width = 40
        # Total time section
        label_desc = 15
        label_target = 17
        label_time = 18
        label_searches = 20

        f.write(f" {'-' * (label_desc + label_target + label_time + label_searches + 11)}\n")
        f.write(f"""| {'Description':<{label_desc}} | {'Target':<{label_target}} | {'Time (sec)':<{label_time}} | {'Number of Searches':<{label_searches}} |\n|{'-' * (label_desc + 1)}-|{'-' * (label_target + 1)}-|{'-' * (label_time + 1)}-|{'-' * (label_searches + 1)}-|\n""")
        f.write(f"| {'Best case':<{label_desc}} | {str(best):<{label_target}} | {t_best * trials:<{label_time}.10f} | {trials:<{label_searches}} |\n")
        f.write(f"| {'Average case':<{label_desc}} | {str(random_target):<{label_target}} | {t_avg * trials:<{label_time}.10f} | {trials:<{label_searches}} |\n")
        f.write(f"| {'Worst case 1':<{label_desc}} | {str(worst1):<{label_target}} | {t_worst1 * trials:<{label_time}.10f} | {trials:<{label_searches}} |\n")
        f.write(f"| {'Worst case 2':<{label_desc}} | {str(worst2):<{label_target}} | {t_worst2 * trials:<{label_time}.10f} | {trials:<{label_searches}} |\n")
        f.write(f" {'-' * (label_desc + label_target + label_time + label_searches + 11)}\n")

        label_width = 20
        f.write("\nAverage time taken per search:\n")
        f.write(f"{'Best case':<{label_width}} : {t_best:.10f} sec\n")
        f.write(f"{'Average case':<{label_width}} : {t_avg:.10f} sec\n")
        f.write(f"{'Worst case':<{label_width}} : {t_worst1:.10f} sec\n")
        f.write(f"{'Worst case':<{label_width}} : {t_worst2:.10f} sec\n")


    print(f"Results written to {output_file}")

if __name__ == '__main__':
    main()
