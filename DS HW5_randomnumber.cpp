#include <random>
#include <ctime>
#include <vector>

std::vector<int> randomnumber(int n){
    std::vector<int> list(n);
    std::default_random_engine rng(std::time(NULL));
    std::uniform_int_distribution<int> number(1, 50000);
    for(int i = 0 ; i < n ; i++){
        list[i] = number(rng);
    }
    return list;
}

//random -> https://cplusplus.com/reference/random/