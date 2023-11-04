import matplotlib.pyplot as plt
import numpy as np
import timeit
import math
import random

def binarySearch(a, x, n):
    left = 0
    right = n - 1
    while left <= right:
        middle = (left + right) // 2
        if x < a[middle]:
            right = middle - 1
        elif x > a[middle]:
            left = middle + 1
        else:
            return middle
    return -1

def selectionSort(a, n):
    for i in range(n):
        j = i
        for k in range(i + 1, n):
            if a[k] > a[j]:
                j = k
        a[i], a[j] = a[j], a[i]

def main():
    binary_times = []
    selection_times = []
    for n in range(0, 100):
        a = random.sample(range(1, 10000), n)
        x = random.randint(1, 10000)
        t1 = timeit.timeit(lambda: binarySearch(sorted(a), x, n), number=1000)
        t2 = timeit.timeit(lambda: selectionSort(a, n), number=1000)
        binary_times.append(t1 * 1000 / 1000)
        selection_times.append(t2 * 1000 / 1000)
    
    plt.plot(range(0, 100), binary_times, label='Binary Search')
    plt.plot(range(0, 100), selection_times, label='Selection Sort')
    
    plt.xlabel('n')
    plt.ylabel('Time (ms)')
    
    plt.xlim(0, 101)
    plt.ylim(0, max(max(binary_times), max(selection_times)) * 1.1)
    
    plt.xticks(np.arange(0,101,5))
    plt.yticks(np.arange(0, max(max(binary_times), max(selection_times)) * 1.15, 0.01))
    
    plt.legend()
    #plt.show()

    print("Binary Search :", binary_times)
    print("Selection Sort :", selection_times)

if __name__ == '__main__':
    main()