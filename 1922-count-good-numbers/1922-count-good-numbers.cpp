class Solution {
private:
    const int mod = 1e9 + 7;
    long long modPow(long long base, long long exp,long long ans) {
        base%=mod;
        while(exp>0){
            if(exp%2==1){
                return modPow(base,exp-1,(ans*base)%mod);
            }
            else{
                return modPow((base*base)%mod,exp/2,ans);
                
            }
        }
        return ans;
    }
public:
    int countGoodNumbers(long long n) {
        long long ans=1;
        long long even_cnt=(n+1)/2;
        long long odd_cnt=n/2;

        long long even_ways = modPow(5, even_cnt,ans);
        long long odd_ways = modPow(4, odd_cnt,ans);

        return (odd_ways*even_ways)%mod;
    }
};