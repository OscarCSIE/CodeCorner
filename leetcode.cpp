#include<iostream>
#include<vector>

using namespace std;

template<class T>
void swap(T& a, T& b){
    T temp = a;
    a = b;
    b = temp;
}

class Solution {
public:
    std::vector<std::vector<int>> sortTheStudents(std::vector<std::vector<int>>& score, int k) {
        for(int i = 0 ; i < score.size() - 1; i++){
        for(int j = 0 ; j < score.size() - i - 1; j++){
            if(score[j][k] > score[j + 1][k]){
                swap(score[j], score[j + 1]);
            }
        }
        std::cout << std::endl;
    }

    std::cout<<"[";
    for(int i = score.size() - 1; i >= 0 ; i--){
        std::cout<<"[";
        for(int j = 0 ; j < score[i].size() ; j++){
            if(j < score[i].size() - 1){
                std::cout << score[i][j] << ",";
            }else{
                std::cout << score[i][j];
            }
        }
        if(i >= 1){
                std::cout <<"],";
            }else{
                std::cout << "]";
            }
    }
    std::cout << "]" << std::endl;
    return score;
    }
};

int main(){
    int k = 2;
    std::vector <std::vector <int> > list = {
        {10,6,90,1},{7,5,101,2},{4,8,3,15}
    };

    for(int i = 0 ; i < list.size() - 1; i++){
        for(int j = 0 ; j < list.size() - i - 1; j++){
            if(list[j][k] > list[j + 1][k]){
                swap(list[j], list[j + 1]);
            }
        }
        std::cout << std::endl;
    }

    std::cout<<"[";
    for(int i = list.size() - 1; i >= 0 ; i--){
        std::cout<<"[";
        for(int j = 0 ; j < list[i].size() ; j++){
            if(j < list[i].size() - 1){
                std::cout << list[i][j] << ",";
            }else{
                std::cout << list[i][j];
            }
        }
        if(i >= 1){
                std::cout <<"],";
            }else{
                std::cout << "]";
            }
    }
    std::cout << "]" << std::endl;
    return 0;
}