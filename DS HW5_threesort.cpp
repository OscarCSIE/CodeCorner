#include <iostream>
#include <random>
#include <ctime>
#include <vector>
#include <fstream>
#include <chrono>

std::vector<int> randomnumber(int n){
    std::vector<int> list(n);
    std::default_random_engine rng(std::time(NULL));
    std::uniform_int_distribution<int> number(1, 50000);
    for(int i = 0 ; i < n ; i++){
        list[i] = number(rng);
    }
    return list;
}

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

void mergesort(std::vector<int>& arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        mergesort(arr, l, m);
        mergesort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

void heapify(std::vector<int>& nums, int n, int index){
        int left = (2 * index) + 1;
        int right = (2 * index) + 2;
        int largest = index;
        if(left < n && nums[left] > nums[largest]){
            largest = left;
        }
        if(right < n && nums[right] > nums[largest]){
            largest = right;
        }
        if(largest != index){
            std::swap(nums[index], nums[largest]);
            heapify(nums, n, largest);
        }
    }

void buildmaxheap(std::vector<int>& nums){
    for(int i = nums.size() / 2 ; i >= 0 ; i--){
        heapify(nums, nums.size(), i);
    }
}

void heapsort(std::vector<int> &nums){
    buildmaxheap(nums);
    for(int i = nums.size() - 1 ; i >= 1 ; i--){
        std::swap(nums[0], nums[i]);
        heapify(nums, i, 0);
        }
    }


int main(){
    int choice;
    std::cout << "1. quickSort\n2. mergeSort\n3. heapSort\nEnter your choice:\n";
    while(std::cin>>choice){
        for(int n = 10 ; n <= 100000 ; n++){
            std::vector<int> arr = randomnumber(n);
            switch(choice){
                case 1:{//quickSort
                    auto start_time = std::chrono::steady_clock::now();
                    quickSort(arr, 0, arr.size() - 1);
                    auto end_time = std::chrono::steady_clock::now();
                    std::cout <<"n = "<< n << "-> " << std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count() / 1000000.0 << " ms" << std::endl;
                    break;
                }
                case 2:{//mergesort
                    auto start_time = std::chrono::steady_clock::now();
                    mergesort(arr, 0, arr.size() - 1);
                    auto end_time = std::chrono::steady_clock::now();
                    std::cout <<"n = "<< n << "-> " << std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count() / 1000000.0 << " ms" << std::endl;
                    break;
                }
                case 3:{//heapsort
                    auto start_time = std::chrono::steady_clock::now();
                    heapsort(arr);
                    auto end_time = std::chrono::steady_clock::now();
                    std::cout <<"n = "<< n << "-> " << std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count() / 1000000.0 << " ms" << std::endl;
                    break;
                }
            }
        }
    }
}