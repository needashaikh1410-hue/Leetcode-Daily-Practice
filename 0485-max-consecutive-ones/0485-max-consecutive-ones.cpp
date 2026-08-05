class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        int maxi=0;
        int consec=0;
        for(int i=0;i<nums.size();i++){
            if(nums[i]==1){
                consec++;
                maxi=max(consec,maxi);
            }
            else{
                consec=0;
            }
        }
        return maxi;
    }
};