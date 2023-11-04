#include<iostream>
#include<vector>

class Solution {
public:
    int removeDuplicates(std::vector<int>& list) {
        int len = list.size();
        int ans = 0;
        for(int i = 1; i < len; i++){
            if(list[i] != list[ans]){
                ans++;
                list[ans] = list[i];
            }
        }
        return ans + 1;
    }
};