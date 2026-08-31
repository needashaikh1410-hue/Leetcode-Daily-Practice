class Solution {
private:

public:
    int numberOfSubstrings(string s) {
        int arr[3]={0};
        int n=s.size();
        int l=0,r=0,ans=0;
        for(;r<n;r++){
            arr[s[r]-'a']++;
            while(arr[0]>0 && arr[1]>0 && arr[2]>0 ){
               ans+=(n-r);
               arr[s[l]-'a']--;
               l++; 
            }
        }
        return ans;

    }
};