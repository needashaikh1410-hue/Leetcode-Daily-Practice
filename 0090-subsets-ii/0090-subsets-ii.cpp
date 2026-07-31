class Solution {
private:
    void solve(int i,vector<int>&curr,vector<int>&nums,vector<vector<int>>&ans){
        ans.push_back(curr);
        for(int index=i;index<nums.size();index++){
            if(index>i && nums[index]==nums[index-1]){
                continue;
            }
            curr.push_back(nums[index]);
            solve(index+1,curr,nums,ans);
            curr.pop_back();
        }

    }
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        vector<vector<int>>ans;
        vector<int>curr;
        solve(0,curr,nums,ans);
        return ans;
    }
};