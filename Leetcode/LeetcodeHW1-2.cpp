#include<iostream>
#include<algorithm>
#include<vector>

class Solution {
public:
    int searchInsert(std::vector<int>& nums, int target) {
        nums.insert(nums.end(), target);
        std::sort(nums.begin(), nums.end());
        auto result = std::find(nums.begin(), nums.end(), target);
        int ans = std::distance(nums.begin(), result);
        return ans;
    }
};
