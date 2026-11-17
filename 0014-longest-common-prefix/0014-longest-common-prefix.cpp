class Solution {
public:
    string longestCommonPrefix(vector<string>& str) {
    if(str.empty()) return "";
    sort(str.begin(),str.end());
    string first=str[0];
    string last=str[str.size()-1];
    string ans="";
    for(int i=0;i<min(first.size(),last.size());i++){
        if(first[i]!=last[i]){
            break;
        }
        ans+=first[i];
    }
    return ans;
    }
};