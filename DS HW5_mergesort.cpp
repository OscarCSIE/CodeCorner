#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>

void merge(std::vector<int>& arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    std::vector<int> left(n1), right(n2);

    for (int i = 0; i < n1; i++){
        left[i] = arr[l + i];
    }
    for (int j = 0; j < n2; j++){
        right[j] = arr[m + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = l;

    while (i < n1 && j < n2) {
        if (left[i] <= right[j]) {
            arr[k] = left[i];
            i++;
        } else {
            arr[k] = right[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = left[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = right[j];
        j++;
        k++;
    }
}

void mergeSort(std::vector<int>& arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}
#include <random>
std::vector<int> randomnumber(int n){
    std::vector<int> list(n);
    std::default_random_engine rng(std::time(NULL));
    std::uniform_int_distribution<int> number(1, 50000);
    for(int i = 0 ; i < n ; i++){
        list[i] = number(rng);
    }
    return list;
}

int main() {
    std::vector<int> list;

    for(int n = 10; n <= 100000 ; n*=10){
        std::ifstream infile("random" + std::to_string(n) + ".txt");

        int number;
        while(infile >> number){
            list.push_back(number);
        }
        infile.close();

        auto start_time = std::chrono::steady_clock::now();
        mergeSort(list, 0, list.size() - 1);
        auto end_time = std::chrono::steady_clock::now();
        
        std::cout <<"n = "<< n << "-> " << std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count() / 1000000.0 << " ms" << std::endl;
    }
    return 0;
}