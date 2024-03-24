#include <iostream>
#include <vector>
#include "..\CodeCorner\DS HW5_randomnumber.cpp"

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

        for(int i = 0 ; i <= end ; i++){
            std::cout<<arr[i]<<" ";
        }
        std::cout<<std::endl;
        
        quickSort(arr, start, j - 1);
        quickSort(arr, j + 1, end);
    }
}

int main(){
    std::vector<int> arr = {26, 5, 37, 1, 61, 11, 59, 15, 48, 19};
    quickSort(arr, 0, arr.size() - 1);
	for (int i = 0 ; i < arr.size() ; i++){
		std::cout << arr[i] << " ";
	}
    std::cout<<std::endl;
	return 0;
}
