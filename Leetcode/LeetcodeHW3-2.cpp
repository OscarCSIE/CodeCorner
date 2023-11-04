#include <vector>
#include <algorithm>

class MinStack {
public:
    std::vector<std::pair<int,int> > stack;
    MinStack(){}
    void push(int val) {
        if(stack.empty()){
            std::pair<int,int> p;
            p.first = val;
            p.second = val;
            stack.push_back(p);
        }else{
            std::pair<int,int> p;
            p.first = val;
            p.second = std::min(val,stack.back().second);
            stack.push_back(p);
        }
    }
    void pop() {
        stack.pop_back();
    }
    int top() {
        return stack.back().first;
    }
    int getMin() {
      return stack.back().second;  
    }
};
