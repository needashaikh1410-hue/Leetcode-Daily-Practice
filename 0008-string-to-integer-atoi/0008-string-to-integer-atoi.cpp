class Solution {
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
    while(i<n && s[i]>='0' && s[i]<='9'){
        int digi=s[i]-'0';
        if(ans>INT_MAX/10 || (ans==INT_MAX/10 && digi>7) ){
            return (sign == 1) ? INT_MAX : INT_MIN;;
        }
        ans=ans*10 +digi;
        i++;
    }
    return sign*ans;
    }
};