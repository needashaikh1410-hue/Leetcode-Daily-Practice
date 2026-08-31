// Binary Subarrays With Sum (Optimal Two-Pointer / AtMost Pattern)
// Problem: https://leetcode.com/problems/binary-subarrays-with-sum/
// Approach: Exactly(goal) = AtMost(goal) - AtMost(goal - 1) using sliding window
// Time Complexity: O(N) where N is the length of array nums
// Space Complexity: O(1) auxiliary space

#include <iostream>
#include <vector>

using namespace std;

class Solution {
private:
    // Helper function to count subarrays with sum <= goal
    int numSubarraysWithSumhelper(const vector<int>& nums, int goal) {
        if (goal < 0) return 0;

        int l = 0, r = 0, sum = 0, cnt = 0;

        for (; r < nums.size(); r++) {
            sum += nums[r];

            // Shrink window if sum exceeds current goal limit
            while (sum > goal) {
                sum -= nums[l];
                l++;
            }

            // Number of valid subarrays ending at index r
            cnt += (r - l + 1);
        }

        return cnt;
    }

public:
    int numSubarraysWithSum(vector<int>& nums, int goal) {
        // Compute: AtMost(goal) - AtMost(goal - 1)
        return numSubarraysWithSumhelper(nums, goal) - numSubarraysWithSumhelper(nums, goal - 1);
    }
};