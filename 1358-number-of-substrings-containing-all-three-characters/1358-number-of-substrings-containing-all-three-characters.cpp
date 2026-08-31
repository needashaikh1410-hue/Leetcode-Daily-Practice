class Solution {
private:

public:
    int numberOfSubstrings(string s) {
        int ls[3]={-1,-1,-1};
        int n=s.size();
        int ans=0;
        for(int i=0;i<n;i++){
            ls[s[i]-'a']=i;
            if (ls[0]!=-1 && ls[1]!=-1 && ls[2]!=-1 ){
               ans+=1+min({ls[0],ls[1],ls[2]});
            }
        }
        return ans;
    }
};