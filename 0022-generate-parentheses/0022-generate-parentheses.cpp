class Solution {
private:
    void solve(int open,int close,int n,string &curr,vector<string>&vec){
        if(close==n && open==n){
            vec.push_back(curr);
            return;
        }
        if(open<n){
            curr.push_back('(');
            solve(open+1,close,n,curr,vec);
            curr.pop_back();
        }
        if(close<open){
            curr.push_back(')');
            solve(open,close+1,n,curr,vec);
            curr.pop_back();}    
    }
public:
    vector<string> generateParenthesis(int n) {
        vector<string> vec;
        string ans;
        solve(0,0,n,ans,vec);
        return vec;
    }
};