#include <iostream>
#include <vector>
#include "..\CodeCorner\DS HW5_randomnumber.cpp"
#include <time.h>
#include <chrono>

void quickSort(std::vector<int>& arr, int start, int end){
    if (start < end) {
        int pivot = arr[start];
        int i = start + 1;
        int j = end;
        while (i <= j) {
            if (arr[i] <= pivot) {
                i++;
            } else if (arr[j] > pivot) {
                j--;
            } else {
                std::swap(arr[i], arr[j]);
            }
        }
        std::swap(arr[start], arr[j]);
        
        quickSort(arr, start, j - 1);
        quickSort(arr, j + 1, end);
    }
}

int main(){
    for(int n = 10 ; n <= 100000 ; n *= 10){
        std::vector<int> arr = randomnumber(n);
        auto start_time = std::chrono::steady_clock::now();
        quickSort(arr, 0, arr.size() - 1);
        auto end_time = std::chrono::steady_clock::now();
        std::cout << "n = " << n << " : " << std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count() << "ns" << std::endl;
    }
	return 0;
}
