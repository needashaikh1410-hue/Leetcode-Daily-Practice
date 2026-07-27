class Solution {
private:
    int helper(const string &s,int i,int ans,int sign){
        if(i >= s.size() || s[i] < '0' || s[i] > '9'){
            return ans*sign;
        }
        int digi=s[i]-'0';
        if(ans>INT_MAX/10 || (ans==INT_MAX/10 && digi>7) ){
            return (sign == 1) ? INT_MAX : INT_MIN;;
        }
        return helper(s,i+1,ans*10+digi,sign);
    }
public:
  int myAtoi(string s) {
    int ans=0,i=0,n=s.size();
    int sign=1;
    while(i<n && s[i]==' '){
        i++;
    }       
    if(i<n && (s[i] == '+' || s[i] == '-')){
        sign=(s[i]=='-')?-1:1;
        i++;
    }
    return helper(s,i,ans,sign);
    }
};