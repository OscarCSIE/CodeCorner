#include <iostream>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <vector>

/*
source:
https://stackoverflow.com/questions/27674009/c-equivalent-of-python-dictionaries
https://www.geeksforgeeks.org/pair-in-cpp-stl/
*/

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

    std::unordered_map<char, int> charCount = myString.frequency(inputString);//put it in

    //not actually asked from us 
    std::vector<std::pair<char, int>/*pair is basically a dictionary in python*/> sorted(charCount.begin(), charCount.end());
    std::sort(sorted.begin(), sorted.end());//sort it

    std::cout << "Character frequencies in the string:" << std::endl;//output it
    for (const auto& character : sorted) {
        std::cout << " ' " << character.first << " ' : " << character.second << " times." << std::endl;
    }

    return 0;
}
//oKf``~~4[][]#G8{}{}sD@@qX  rJ7$$\\||<<>>,,..Bt!!T%%3^^y&&M**w((W))Z__6==++N??//z2UoVI 1pe9vA5;;hYi Q0xuPjS''6mRlC""c::FnEaObXgHTysfdgyijkusadgfjyadhfkjhas++N2UoVI1pe9vA5yjvYiQ0xuPjS''6mRlC""c::FnEaObXgHTysfdgyijkusadgfjyadhfkjhasdgidhfdewagtgyfhudaiyfuahgikuhfdshBrBYa1VnpAVHqBb7gX2WcIe1gevGRyCKmIRZ23mPakjbjdez0pARMyXvBtbl4uYLhWewBD4MEvT1P8JN0tfDwJsYsTzUAC5S8Jk0SLEQVRPafgKoOa8dJAmxpSSPi0IBqQlyecsXqHMoJBZTMG5Mh9OBcMgfeN46eYIoABLykHyjdrdjhfgcrftxgrwagtgdhtyfjythdryfhudaiyfuahgikuhfdsKf``~~4[][]#G8{}{}sD@@qX  rJ7$$\\||<<>>,,..Bt!!T%%3^^y&&M**w((W))dtjfrthadrftylkjhgfZ__6==kjhdezshjljkheddfgjkhkl''6mRlC""c::FnEaObXgHTysfdgyijkusadgfjyadhfkjhasdgidhfdyjvewagtgyfhudaiyfuahgikuhfdsKf``~~4[][]#G8{}{}sD@@qX  rJ7$$\\||<<>>,,..gBt!!T%%3^^y&&M**w((W))Z__6==cYssdK8GpWUEO5opNq5qI5exkrv5lv8ZzeuJlXwYbxVF9HrxQCK6fmUgY5AkmIaL3I1IOYnctUxXkPrYTge7IIFBKPDqyciRAB2kfc4wa6U6czGpZmx06vAzdFcdTe23C24WTIhta1ECVY5nTwrvvUUA89T3N6RmWkkGMSl2KsNtWsplMke6tV3AmPe2TOvRT9SXfrbPxY6N0lYgwokOt5nE7oQuOFU8bYtL4865sbdH9u174SvGckq2WyEv627gji7FDc0qN5hskrytmfyjfyggxhfufjdnxfrgqAkKezsCMVopf8B3ysR9lYwmk3PbgN7ASXpxNrmahlQEu8gGJLUDPMRiN7jFINirLlO4vUCDhofGIjErr1xmS2hdU