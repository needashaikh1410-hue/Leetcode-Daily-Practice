class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_map<char,int> mpp;
        int max_len=0;
        int left=0,right=0;
        for(;right<s.size();right++){
            char ch=s[right];
            if(mpp.find(ch)!=mpp.end()){
                left=max(left,mpp[ch]+1);
            }
            mpp[ch]=right;
            max_len=max(max_len,right-left+1);
        }
        return max_len;

    }
};