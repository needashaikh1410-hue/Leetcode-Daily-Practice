class Solution {
private:
    int atmost(vector<int>& s,int k){
        if(k<0){
            return 0;
        }
        int l=0,r=0,cnt=0;
        unordered_map<int,int>mpp;
        for(;r<s.size();r++){
            mpp[s[r]]++;
            while(mpp.size()>k){
                mpp[s[l]]--;
                if(mpp[s[l]]==0){
                    mpp.erase(s[l]);
                }
                l++;
            }
            cnt+=r-l+1;
        }
        return cnt;
    } 
public:
    int subarraysWithKDistinct(vector<int>& nums, int k) {
        return atmost(nums,k)-atmost(nums,k-1);
    }
};