
using namespace std;

class Solution {
private:
    long long total_hr(vector<int>& piles, int x) {
        long long ttl = 0;
        for (int i = 0; i < piles.size(); i++) {
            ttl += ((piles[i]+x-1)/x);
        }
        return ttl;
    }

public:
    int minEatingSpeed(vector<int>& piles, int h) {
        int max_pile = *max_element(piles.begin(), piles.end());
        int low = 1, high = max_pile;
        
        while(low <= high){
            int mid = low + ((high - low) / 2);
            long long hr = total_hr(piles, mid);
            
            if(hr <= h){
                high = mid - 1;
            }   
            else{
                low = mid + 1;
            }
        }
        return low;
    }
};