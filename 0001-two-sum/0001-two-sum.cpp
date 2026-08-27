#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> ans;
        int n = nums.size();
        
        vector<pair<int, int>> indexed_nums(n);
        for(int i = 0; i < n; i++) {
            indexed_nums[i] = {nums[i], i};
        }
        
        sort(indexed_nums.begin(), indexed_nums.end());
        
        int left = 0;
        int right = n - 1;
        
        while(left < right) {
            int sum = indexed_nums[left].first + indexed_nums[right].first;
            
            if(sum < target) {
                left++;
            }
            else if(sum > target) {
                right--;
            }
            else if(sum == target) {
                ans.insert(ans.begin(), {indexed_nums[left].second, indexed_nums[right].second});
                break;
            }
        }
        return ans;
    }
};