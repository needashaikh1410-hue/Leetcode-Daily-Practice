#include <vector>

using namespace std;

class Solution {
private:
    void solve(int i, int target, vector<int>& curr, vector<int>& nums, vector<vector<int>>& ans) {
        // Base Case 1: Target achieved -> save valid combination
        if (target == 0) {
            ans.push_back(curr);
            return;
        }

        // Base Case 2: Target exceeded or out of bounds -> backtrack
        if (target < 0 || i == nums.size()) {
            return;
        }

        // Choice 1: Skip current element and move to next index
        solve(i + 1, target, curr, nums, ans);

        // Choice 2: Pick current element (stay at index i for unlimited reuse)
        curr.push_back(nums[i]);
        solve(i, target - nums[i], curr, nums, ans);
        curr.pop_back(); // Backtrack
    }

public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<int> curr;
        vector<vector<int>> ans;
        solve(0, target, curr, candidates, ans);
        return ans;
    }
};