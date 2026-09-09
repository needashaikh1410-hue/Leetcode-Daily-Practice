class Solution {
private:
    static bool comp(const vector<int> &arr1,const vector<int> &arr2){
        return arr1[1]<arr2[1];
    }
public:
    int eraseOverlapIntervals(vector<vector<int>>& arr) {
        sort(arr.begin(),arr.end(),comp);
        int cnt=1,lastel=arr[0][1];
        int n=arr.size();
        for(int i=1;i<n;i++){
            if(arr[i][0]>=lastel){
                lastel=arr[i][1];
                cnt++;
            }
        }
        return n-cnt;
    }
};