class Solution {
public:
    string minWindow(string s, string t) {
        int n = s.size(), m = t.size();
        if (m > n) return "";

        int hash[256] = {0};
        int cnt = 0;

        // Step 1: Pre-populate character requirements from string t
        for (int i = 0; i < m; i++) {
            hash[t[i]]++;
        }

        int l = 0, r = 0;
        int min_len = INT_MAX;
        int start = -1;

        // Step 2: Expand window with right pointer
        for (; r < n; r++) {
            if (hash[s[r]] > 0) {
                cnt++;
            }
            hash[s[r]]--;

            // Step 3: Shrink window from left while it remains valid
            while (cnt == m) {
                if (r - l + 1 < min_len) {
                    min_len = r - l + 1;
                    start = l;
                }

                // Remove character at s[l] from window
                hash[s[l]]++;
                if (hash[s[l]] > 0) {
                    cnt--;
                }
                l++;
            }
        }

        return (start == -1) ? "" : s.substr(start, min_len);
    }
};