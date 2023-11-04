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

def swap(a,b):
    a,b = b,a

def selectionSort(a, n):
    for i in range(n):
        j = i
        for k in range(i + 1, n):
            if a[k] > a[j]:
                j = k
        a[i], a[j] = a[j], a[i]

def main():
    times = []
    for n in range(0, 100):
        a = sorted(random.sample(range(1, 10001), n))
        x = random.randint(1, 10000)
        t = timeit.timeit(lambda: binarySearch(a, x, n), number=1000)
        times.append(t)
    plt.plot(range(1, 101), times)
    plt.xlabel('n')
    plt.ylabel('Time (s)')
    plt.show()

if __name__ == '__main__':
    main()