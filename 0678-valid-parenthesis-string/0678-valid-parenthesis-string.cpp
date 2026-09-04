class Solution {
public:
    bool checkValidString(string s) {
        int max=0;
        int mini=0;
        for(int i=0;i<s.size();i++){
            if(s[i]=='('){
                max++;
                mini++;
            }
            else if (s[i]==')'){
                max--;
                mini--;
            }
            else{
                max++;
                mini--;    
            }
            if(mini<0){mini=0;}
            if(max<0){return false;}
        }
        return mini==0;
    }
};