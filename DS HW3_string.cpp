#include <iostream>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <vector>


class String {
    private:
    std::string m_string;
    
    public:
    String(const std::string& input){
        m_string = input;
    }

    virtual std::unordered_map<char, int> frequency(const std::string m_string);
};


std::unordered_map<char, int> String::frequency(const std::string m_string) {
    
    std::unordered_map<char, int> charCount;

    for (char c : m_string){
        if (c >= 32 && c <= 126) {
            charCount[c]++;
        }
    }
    return charCount;
}

int main() {
    std::cout << "Input your desired string(Assuming ASCII input): " << std::endl;

    std::string inputString;
    getline(std::cin, inputString);

    String myString(inputString);

    std::unordered_map<char, int> charCount = myString.frequency(inputString);

    std::vector<std::pair<char, int>> sorted(charCount.begin(), charCount.end());
    std::sort(sorted.begin(), sorted.end());

    std::cout << "Character frequencies in the string:" << std::endl;
    for (const auto& character : sorted) {
        std::cout << " ' " << character.first << " ' : " << character.second << " times." << std::endl;
    }
    return 0;
}