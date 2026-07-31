class Solution {
private:
    void solve(int start,int target,int k,vector<int>&curr,vector<vector<int>>&ans){
        if(k==0 && target==0){
            ans.push_back(curr);
            return;}
        for(int i=start;i<=9;i++){
        if(k==0){return;}
        if(i>target){
            break;}
        curr.push_back(i);
        solve(i+1,target-i,k-1,curr,ans);
        curr.pop_back();
        }
    }
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<int>curr;
        vector<vector<int>>ans;
        solve(1,n,k,curr,ans);
        return ans;
    }
};