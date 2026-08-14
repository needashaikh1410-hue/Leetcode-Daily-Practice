

#include <iostream>
#include <stack>
#include <algorithm>

using namespace std;

class MinStack {
private:
    // Pair stores {element_value, current_minimum}
    stack<pair<int, int>> st;

public:
    MinStack() {
    }
    
    void push(int value) {
        if (st.empty()) {
            st.push({value, value}); // Fix 1 & 2: Use curly braces for pairs and st.push()
        } else {
            int currentMin = min(value, st.top().second);
            st.push({value, currentMin}); // Fix 3: Proper syntax and matching parenthesis
        }
    }
    
    void pop() {
        if (!st.empty()) {
            st.pop(); // Fix 4: Void return type, no 'return ans;'
        }
    }
    
    int top() {
        return st.top().first;
    }
    
    int getMin() {
        return st.top().second;
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(value);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */