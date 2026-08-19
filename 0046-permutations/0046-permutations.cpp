class Solution {
private:
    void solve(vector<bool> &visited,vector<int> &curr,vector<vector<int>> &ans,vector<int>& nums){
        if(curr.size()==nums.size()){
            ans.push_back(curr);
        }
        for(int i=0;i<nums.size();i++){
            if(visited[i]==true){continue; }
            visited[i]=true;
            curr.push_back(nums[i]);
            solve(visited,curr,ans,nums);
            curr.pop_back();
            visited[i]=false;

        }

    }
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<int> curr;
        vector<vector<int>>ans;
        vector<bool>visited(nums.size(),false);
        solve(visited,curr,ans,nums);
        return ans;
    }
};