class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int, vector<int>, greater<int>> min_heap;

        // Phase 1: Push first k elements
        for (int i = 0; i < k; i++) {
            min_heap.push(nums[i]);
        }

        // Phase 2: Process remaining N - k elements
        for (int i = k; i < nums.size(); i++) {
            if (nums[i] > min_heap.top()) {
                min_heap.pop();
                min_heap.push(nums[i]);
            }
        }

        return min_heap.top();
    }
};