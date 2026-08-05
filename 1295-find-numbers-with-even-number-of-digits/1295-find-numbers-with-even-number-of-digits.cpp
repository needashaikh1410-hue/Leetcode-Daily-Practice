class Solution {
private:
    int cntdig(int n){
        int ans=0;
        while(n!=0){
            n=n/10;
            ans+=1;
        }
        return ans;
    }
public:
    int findNumbers(vector<int>& nums) {
        int ans=0;
        for(int i=0;i<nums.size();i++){
            if(cntdig(nums[i])%2==0){
                ans++;
            }
        }
        return ans;
    }
};