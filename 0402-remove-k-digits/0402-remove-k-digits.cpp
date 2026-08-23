class Solution {
public:
    string removeKdigits(string num, int k) {
        int n=num.size();
        if(k==n){
            return "0";
        }
        stack<char> st;
        for(int i=0;i<n;i++){
            while(!st.empty() && k>0 && num[i]<st.top() ){
                st.pop();
                k--;
            }
            st.push(num[i]);
        }
        while(k>0){
            k--;
            st.pop();
        }
        if(st.empty()){
            return "0";
        }
        string res="";
        while(!st.empty()){
            res+=st.top();
            st.pop();
        }
        while(res.size()!=0 && res.back()=='0'){
            res.pop_back();
        }
        if(res.empty()){ return "0";}
        reverse(res.begin(),res.end());
        return res;
    }
};