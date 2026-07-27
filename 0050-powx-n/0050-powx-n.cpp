class Solution {
private:
    double helper(double x,long long nn,double ans){
        if(nn<=0){
            return ans;
        }
        if(nn%2==1){
                ans=ans*x;
                nn=nn-1;
                return helper(x,nn,ans);
        }
            else{
                x*=x;
                nn/=2;
                return helper(x,nn,ans);
            }
            return 0.0;
    }
public:
    double myPow(double x, int n) {
        long long nn= n;
        double ans=1.0;
        if(nn<0){nn=-nn;}
        ans=helper(x,nn,ans);
        if(n<0){ans=1.0/ans;};
        return ans;
    }
};