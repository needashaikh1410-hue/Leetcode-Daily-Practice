class Solution {
private:
    void solve(int i,vector<vector<int>> &ans,vector<int> &curr,vector<int> &nums){
        ans.push_back(curr);
        for(int index=i;index<nums.size();index++){
            if(index>i && nums[index]==nums[index-1]){
                continue;
            }
            curr.push_back(nums[index]);
            solve(index+1,ans,curr,nums);
            curr.pop_back();
        }
    }
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        vector<int>curr;
        vector<vector<int>> ans;
        solve(0,ans,curr,nums);
        return ans;
    }
};