class Solution {
private:
    void solve(int i,int target,vector<int>& nums,vector<int>&curr,vector<vector<int>>&ans){
        if(target==0){
            ans.push_back(curr);
            return;
        }
        for(int index=i;index<nums.size();index++){
            if(nums[index]>target){
                break;
            }
            if(index>i && nums[index]==nums[index-1]){
                continue;
            }
            curr.push_back(nums[index]);
            solve(index+1,target-nums[index],nums,curr,ans);
            curr.pop_back();
        }
    }
public:
    vector<vector<int>> combinationSum2(vector<int>& nums, int target) {
        sort(nums.begin(),nums.end());
        vector<int>curr;
        vector<vector<int>>ans;
        solve(0,target,nums,curr,ans);
        return ans;
    }
};