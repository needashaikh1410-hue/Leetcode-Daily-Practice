class Solution {
private:
    void solve(int i,int target,vector<int>&nums,vector<int>&curr,vector<vector<int>> &ans){
        if(target==0){
            ans.push_back(curr);
            return;
        }
        if(target<0){
            return;
        }
        if(i==nums.size()){
            return;
        }
        solve(i+1,target,nums,curr,ans);

        curr.push_back(nums[i]);
        solve(i,target-nums[i],nums,curr,ans);
        curr.pop_back();
    }
public:
    vector<vector<int>> combinationSum(vector<int>& nums, int target) {
        vector<int>curr;
        vector<vector<int>>ans;
        solve(0,target,nums,curr,ans);
        return ans;
    }
};