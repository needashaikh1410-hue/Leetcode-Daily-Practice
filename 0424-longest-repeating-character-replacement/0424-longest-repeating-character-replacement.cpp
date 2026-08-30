class Solution {
public:
    int characterReplacement(string s, int k) {
        int max_len=0;
        int r=0,l=0;
        int n=s.size();
        int hash[26]={0};
        int max_freq=0;
        for(int r=0;r<n;r++){    
            hash[s[r]-'A']++;
            max_freq=max(max_freq,hash[s[r]-'A']);
            if((r-l+1)-max_freq>k){
                hash[s[l]-'A']--;
                l++;
            }
            if((r-l+1)-max_freq<=k){
                max_len=max(max_len,r-l+1);
            }

        }
        return max_len;

    }
};