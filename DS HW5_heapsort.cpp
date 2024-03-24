#include <iostream>
#include "..\CodeCorner\DS HW5_randomnumber.cpp"

void heapify(std::vector<int>& nums, int n, int i){
        int left = (2 * i) + 1;
        int right = (2 * i) + 2;
        int largest = i;
        if(left < n && nums[left] > nums[largest]){
            largest=left;
        }
        if(right < n && nums[right] > nums[largest]){
            largest = right;
        }
        if(largest != i){
            std::swap(nums[i], nums[largest]);
            heapify(nums, n, largest);
        }
    }

void buildmaxheap(std::vector<int>& nums){
    for(int i = nums.size() - 2 / 2 ; i >= 0 ; i--){
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
    std::vector<int> arr = {26, 5, 37, 1, 61, 11, 59, 15, 48, 19};
    heapsort(arr);
	for (int i = 0 ; i < 10 ; i++){
		std::cout << arr[i] << " ";
	}
    std::cout<<std::endl;
	return 0;
}
