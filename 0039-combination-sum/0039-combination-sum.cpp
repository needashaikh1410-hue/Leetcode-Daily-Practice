class Solution {
private:
   void solve(int i,int target,vector<int>& curr,vector<int>& nums,vector<vector<int>>&ans){
    if(target==0){
        ans.push_back(curr);
        return ;
    }
    if(target<0){
        return;
    }
    if(i==nums.size()){
        return;
    }
    solve(i+1,target,curr,nums,ans);

    curr.push_back(nums[i]);
    solve(i,target-nums[i],curr,nums,ans);
    curr.pop_back();

   }
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<int> curr;
        vector<vector<int>>ans;
        solve(0,target,curr,candidates,ans);
        return ans;
    }
};