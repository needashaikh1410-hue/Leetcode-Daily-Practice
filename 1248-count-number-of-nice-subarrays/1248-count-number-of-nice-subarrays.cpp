// Count Number of Nice Subarrays (Optimal Two-Pointer / AtMost Pattern)
// Problem: https://leetcode.com/problems/count-number-of-nice-subarrays/
// Approach: Transform odd numbers to 1 (nums[i] % 2), then apply Exactly(k) = AtMost(k) - AtMost(k - 1)
// Time Complexity: O(N) where N is the length of array nums
// Space Complexity: O(1) auxiliary space

#include <iostream>
#include <vector>

using namespace std;

class Solution {
private:
    // Helper function to count subarrays with at most 'goal' odd numbers
    int countSubarraysAtMostGoal(const vector<int>& nums, int goal) {
        if (goal < 0) return 0;

        int l = 0, r = 0, sum = 0, cnt = 0;

        for (; r < nums.size(); r++) {
            // Count odd numbers (odd % 2 = 1, even % 2 = 0)
            sum += nums[r] % 2;

            // Shrink window if odd count exceeds goal limit
            while (sum > goal) {
                sum -= nums[l] % 2;
                l++;
            }

            // Number of valid subarrays ending at index r
            cnt += (r - l + 1);
        }

        return cnt;
    }

public:
    int numberOfSubarrays(vector<int>& nums, int k) {
        // Compute: AtMost(k) - AtMost(k - 1)
        return countSubarraysAtMostGoal(nums, k) - countSubarraysAtMostGoal(nums, k - 1);
    }
};