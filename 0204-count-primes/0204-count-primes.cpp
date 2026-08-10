class Solution {
public:
    int countPrimes(int n) {
        int ans=0;
        vector<int> arr(n+1,1);
        for(int i=2;i*i<=n;i++){
            if(arr[i]==1){
                for(int j=i*i;j<=n;j+=i){
                    arr[j]=0;
                }
            }
        }
        for(int i=2;i<n;i++){
            if(arr[i]==1){
                ans++;
            }
        }
        return ans;
    }
};