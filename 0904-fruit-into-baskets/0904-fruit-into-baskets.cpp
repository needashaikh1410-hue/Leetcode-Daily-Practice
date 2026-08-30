class Solution {
public:
    int totalFruit(vector<int>& arr) {
        int max_len=0,l=0,r=0;
        unordered_map<int,int> mpp;
        for(;r<arr.size();r++){
            mpp[arr[r]]++;
            if(mpp.size()>2){
                while(mpp.size()>2){
                    mpp[arr[l]]--;
                    if(mpp[arr[l]]==0){
                        mpp.erase(arr[l]);
                    }
                    l++;
                }
            }
            max_len=max(max_len,r-l+1);
        }
        return max_len;
    }
};