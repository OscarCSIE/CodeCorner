#include <random>
#include <ctime>

int* randomnumber(int n){
    int* list = new int[n];
    std::default_random_engine rng(std::time(NULL));
    std::uniform_int_distribution<int> number(1, 50000);
    for(int i = 0 ; i < n ; i++){
        *(list + i) = number(rng);
    }
    return list;
}

//random -> https://cplusplus.com/reference/random/