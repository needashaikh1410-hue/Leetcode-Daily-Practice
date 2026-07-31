class Solution {
private:
    const vector<string> pad = {
        "",     "",     "abc",  "def", 
        "ghi",  "jkl",  "mno",         
        "pqrs", "tuv",  "wxyz"         
    };
    void solve(int index,const string& digits,string &curr,vector<string>&ans){
        if(index==digits.size()){
            ans.push_back(curr);
            return;
        }
        int dig=digits[index]-'0';
        const string& letters = pad[dig];
        for(char c: letters){
            curr.push_back(c);
            solve(index+1,digits,curr,ans);
            curr.pop_back();
        }
    }
public:
    vector<string> letterCombinations(string digits) {
        if(digits.empty()){return {};}
        vector<string>ans;
        string curr="";
        solve(0,digits,curr,ans);
        return ans;
    }
};