#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

int main() {
    int m = 1000;
    int n = 1000;
    std::srand(std::time(0));

    std::ofstream outputFile("input numbers.txt");

    if (!outputFile.is_open()) {
        std::cerr << "Error opening the file for writing."<< std::endl;
        return 1;
    }
    
    outputFile << m << std::endl;
    for (int i = 0; i < m; i++) {
        // int randomInt1 = std::rand() % 21 - 10;
        int randomInt1 = (i % 2 == 0) ? 0 : (std::rand() % 21 - 10);
        int randomInt2 = m - i; 

        outputFile << randomInt1 << " " << randomInt2 << std::endl;
    }

    outputFile << n << std::endl;
    for (int i = 0; i < n; i++) {
        // int randomInt1 = std::rand() % 21 - 10;
        int randomInt1 = (i % 2 == 0) ? 0 : (std::rand() % 21 - 10);
        int randomInt2 = n - i;

        outputFile << randomInt1 << " " << randomInt2 << std::endl;
    }
    outputFile.close();

    std::cout << "Generated Output" << std::endl;

    return 0;
}
