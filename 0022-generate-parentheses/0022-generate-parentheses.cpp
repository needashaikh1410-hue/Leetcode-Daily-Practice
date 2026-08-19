class Solution {
private:
    void solve(int open ,int close,int n,string &curr,vector<string> &ans){
        if(close==n && open==n){
            ans.push_back(curr);
            return;
        }
        if(open<n){
            curr+='(';
            solve(open+1,close,n,curr,ans);
            curr.pop_back();
        }
        if(close<open){
            curr+=')';
            solve(open,close+1,n,curr,ans);
            curr.pop_back();
        }
        
    }
public:
    vector<string> generateParenthesis(int n) {
        string curr="";
        vector<string>ans;
        solve(0,0,n,curr,ans);
        return ans;
    }
};