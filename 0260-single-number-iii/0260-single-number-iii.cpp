#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution { 
public:     
    vector<int> singleNumber(vector<int>& nums) {
        long long xxor = 0;
        for (int i = 0; i < nums.size(); i++) {
            xxor ^= nums[i];
        }

        // Isolate the rightmost set bit using (xxor ^ (xxor - 1)) & xxor
        long long rightmost = (xxor ^ (xxor - 1)) & xxor;
        
        int b1 = 0, b2 = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (rightmost & nums[i]) {
                b1 ^= nums[i];
            } else {
                b2 ^= nums[i];
            }       
        }

        // Guarantee increasing order
        if (b1 > b2) {
            swap(b1, b2);
        }

        return {b1, b2};
    }
};