class Solution {
public:
    int longestOnes(vector<int>& nums, int k) {
        int r=0,l=0,max_len=0,zero=0;
        for(;r<nums.size();r++){
            if(nums[r]==0){
                zero++;
            }
            if(zero>k){
                    if(nums[l]==0){
                        zero--;
                    }
                l+=1;
                
            }
            if(zero<=k){
            int len=r-l+1;
            max_len=max(max_len,len);}

        }

        return max_len;
    }
};