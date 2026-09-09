class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& arr, vector<int>& newi) {
        vector<vector<int>> res;
        int n=arr.size();
        int i=0;
        while(i<n && arr[i][1]<newi[0]){
            res.push_back(arr[i]);
            i++;
        }
        while(i<n && arr[i][0]<=newi[1]){
            newi[0]=min(newi[0],arr[i][0]);
            newi[1]=max(newi[1],arr[i][1]);
            i++;
        }
        res.push_back(newi);
        while(i<n){
            res.push_back(arr[i]);
            i++;
        }
        return res;
    }
};