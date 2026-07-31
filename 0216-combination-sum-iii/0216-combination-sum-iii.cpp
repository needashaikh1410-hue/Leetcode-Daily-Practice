class Solution {
private:
    void solve(int i,int target,int k,vector<int>&curr,vector<vector<int>>&ans){
        if(k==0 && target==0){
            ans.push_back(curr);
            return;
        }
        if(target<0||i>9 ||k<0){
            return;
        }
        solve(i+1,target,k,curr,ans);
        curr.push_back(i);
        solve(i+1,target-i,k-1,curr,ans);
        curr.pop_back();
    }
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<int>curr;
        vector<vector<int>>ans;
        solve(1,n,k,curr,ans);
        return ans;
    }
};