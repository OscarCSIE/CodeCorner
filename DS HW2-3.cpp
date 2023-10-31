#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include <iomanip>

// Selection sort function
void selectionSort(std::vector<int>& list, int n) {
    for (int i = 0; i < n; ++i) {
        int j = i;
        for (int k = i + 1; k < n; ++k) {
            if (list[k] > list[j]) {
                j = k;
            }
        }
        std::swap(list[i], list[j]);
    }
}

int main() {
    std::vector<double> selection_times;

    for (int n = 1; n <= 100; ++n) {
        std::vector<int> list;
        for (int i = 0; i < n; ++i) {
            list.push_back(std::rand() % 10000 + 1);
        }

        auto start_time = std::chrono::high_resolution_clock::now();
        
        selectionSort(list, n);
        
        auto end_time = std::chrono::high_resolution_clock::now();
        
        double t = static_cast<double>(std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count());

        selection_times.push_back(t);
    }


    std::cout << "Selection Sort :\n";
    for (double time : selection_times) {
        std::cout << std::fixed << std::setprecision(5) << time << "ns\n";
    }
    std::cout << std::endl;

    return 0;
}