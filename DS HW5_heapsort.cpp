#include <iostream>
#include <vector>
#include "..\CodeCorner\DS HW5_randomnumber.cpp"
#include <chrono>

void heapify(std::vector<int>& nums, int n, int index){
        int left = (2 * index) + 1;
        int right = (2 * index) + 2;
        int largest = index;
        if(left < n && nums[left] > nums[largest]){
            largest=left;
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
    for(int n = 10 ; n <= 100000 ; n *= 10){
        std::vector<int> arr = randomnumber(n);
        auto start_time = std::chrono::steady_clock::now();
        heapsort(arr);
        auto end_time = std::chrono::steady_clock::now();
        std::cout << "n = " << n << " : " << std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count() << "ns" << std::endl;
    }
	return 0;
}
