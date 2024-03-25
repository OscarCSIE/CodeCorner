#include <random>
#include <ctime>
#include <vector>
#include <fstream>

std::vector<int> randomnumber(int n){
    std::vector<int> list(n);
    std::default_random_engine rng(std::time(NULL));
    std::uniform_int_distribution<int> number(1, 50000);
    for(int i = 0 ; i < n ; i++){
        list[i] = number(rng);
    }
    return list;
}

int main(){
    for(int n = 10 ; n <= 100000 ; n++){
        std::vector<int> arr = randomnumber(n);
        std::string filename = "random" + std::to_string(n) + ".txt";
        std::ofstream file(filename);
        for(int i = 0 ; i < n ; i++){
            file << arr[i] << std::endl;
        }
        file.close();
    }
    return 0;
}

//uniform_int_distribution -> https://cplusplus.com/reference/random/uniform_int_distribution/

//random -> https://cplusplus.com/reference/random/