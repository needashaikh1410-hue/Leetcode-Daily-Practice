#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int candy(vector<int>& ratings) {
        int n = ratings.size();
        if (n <= 1) return n;

        int sum = 1;
        int i = 1;

        while (i < n) {
            if (ratings[i] == ratings[i - 1]) {
                sum += 1;
                i++;
                continue;
            }

            // Upward slope
            int peak = 0;
            while (i < n && ratings[i] > ratings[i - 1]) {
                peak++;
                sum += peak + 1;
                i++;
            }

            // Downward slope
            int downward = 0;
            while (i < n && ratings[i] < ratings[i - 1]) {
                downward++;
                sum += downward;
                i++;
            }

            // Correct peak overlap if the downward slope is longer than or equal to the upward slope
            if (downward > peak) {
                sum += (downward - peak);
            }
        }

        return sum;
    }
};