#include <iostream>
#include <vector>
#include <fstream>
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
    std::vector<int> list;

    for(int n = 10; n <= 100000 ; n *= 10){
        std::ifstream infile("random" + std::to_string(n) + ".txt");

        int number;
        while(infile >> number){
            list.push_back(number);
        }
        infile.close();

        auto start_time = std::chrono::high_resolution_clock::now();
        quickSort(list, 0, list.size() - 1);
        auto end_time = std::chrono::high_resolution_clock::now();
        
        std::cout <<"n = "<< n << "-> " << std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count() / 1000000.0 << " ms" << std::endl;
    }
	return 0;
}
