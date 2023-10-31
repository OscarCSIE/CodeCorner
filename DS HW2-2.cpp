#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include <iomanip>
#include <string>

// Binary search function
int binarySearch(std::vector<int>& list, const int x, const int n) {
    int left = 0;
    int right = n - 1;
    while (left <= right) {
        int middle = (left + right) / 2;
        if (x < list[middle]) {
            right = middle - 1;
        } else if (x > list[middle]) {
            left = middle + 1;
        } else {
            return middle;
        }
    }
    return -1;
}

int main() {
    std::vector<double> binary_times;

    for (int n = 1; n <= 100; n++) {
        std::vector<int> list;
        for (int i = 0; i < n; ++i) {
            list.push_back(std::rand() % 10000 + 1);
        }
        std::sort(list.begin(), list.end());

        int x = list.at(int(std::rand()) % int(list.size()));

        auto start_time = std::chrono::high_resolution_clock::now();
        
        int temp_time = binarySearch(list, x, n);
        
        auto end_time = std::chrono::high_resolution_clock::now();
        
        double t = static_cast<double>(std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count());

        binary_times.push_back(t);
    }

    std::cout << "Binary Search :\n";
    for (auto time : binary_times) {
        std::cout << " " << std::fixed << std::setprecision(5) << time << " ns\n";
    }
    
    std::cout << std::endl; 
    
    return 0;
}