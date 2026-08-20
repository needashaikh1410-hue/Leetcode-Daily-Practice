
class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        stack<int> st;
        unordered_map<int, int> ngeMap;

        for (int i = nums2.size() - 1; i >= 0; i--) {
            while (!st.empty() && st.top() <= nums2[i]) {
                st.pop();
            }

            if (st.empty()) {
                ngeMap[nums2[i]] = -1;
            } else {
                ngeMap[nums2[i]] = st.top();
            }

            st.push(nums2[i]);
        }

        vector<int> mainans(nums1.size());
        for (int i = 0; i < nums1.size(); i++) {
            mainans[i] = ngeMap[nums1[i]];
        }

        return mainans;
    }
};