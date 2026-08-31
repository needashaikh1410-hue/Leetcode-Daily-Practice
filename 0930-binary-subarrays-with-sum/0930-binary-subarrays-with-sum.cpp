class Solution {
private:
int numSubarraysWithSumhelper(vector<int>& nums, int goal) {
        if(goal<0){return 0;};
        int r=0,l=0,sum=0,cnt=0;
        for(;r<nums.size();r++){
            sum+=nums[r];
            while(sum>goal){
                sum-=nums[l];
                l++;
            }
            cnt+=r-l+1;
        }
        return cnt;
    }
public:
    int numSubarraysWithSum(vector<int>& nums, int goal) {
        if(goal<0){return 0;};
        int r=0,l=0,sum=0,cnt=0;
        for(;r<nums.size();r++){
            sum+=nums[r];
            while(sum>goal){
                sum-=nums[l];
                l++;
            }
            cnt+=r-l+1;
        }
        return cnt-numSubarraysWithSumhelper(nums,goal-1);
    }
};