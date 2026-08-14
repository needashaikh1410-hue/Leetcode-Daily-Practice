class MinStack {
private:
    long long mini=INT_MAX;
    stack<long long >st;
public:
    MinStack() {
        
    }
    
    void push(int value) {
        if(st.empty()){
            mini=value;
            st.push(value);
        }
        else{
            if(value<mini){
                long long val=value;
                long long x=val*2-mini;
                mini=value;
                st.push(x);
            }
            else{
                st.push(value);
            }
        }
    }
    
    void pop() {
        if(st.empty()){return;}
        if(st.top()<mini){
            mini=2*mini-st.top();
            st.pop();
        }
        else{
            st.pop();
        }
    }
    
    int top() {
        if(st.empty()){
            return -1;
        }
        if(st.top()<mini){
            return mini;
        }
        else{
            return st.top();
        }
    }
    
    int getMin() {
        return mini;
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