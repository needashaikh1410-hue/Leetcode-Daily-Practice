class Solution {
private:
    int max_string(const string &s,int left,int right){
        while(left>=0 && right<s.size() && s[left]==s[right]){
            left--;
            right++;
        }
        return right-left-1;
    }
public:
    string longestPalindrome(string s) {
        int maxlen=0,start=0,n=s.size();
        for(int i=0;i<n;i++){
            int len1= max_string(s,i,i);
            int len2=max_string(s,i,i+1);
            int curr_max=max(len1,len2);
            if(curr_max>maxlen){
                maxlen=curr_max;
                start=i-((curr_max-1)/2);
            }
        }
        return s.substr(start,maxlen);
    }
};