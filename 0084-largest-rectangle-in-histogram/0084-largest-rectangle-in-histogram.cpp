class Solution {
private:
    vector<int> findpse(vector<int>&arr){
        stack<int> st;
        vector<int> ans(arr.size());
        for(int i=0;i<arr.size();i++){
            while(!st.empty() && arr[st.top()]>=arr[i]){
                st.pop();
            }
            if(st.empty()){
                ans[i]=-1;
            }else{
                ans[i]=st.top();
            }
            st.push(i);
        }
        return ans;
    }
    vector<int> findnse(vector<int>&arr){
        stack<int> st;
        vector<int> ans(arr.size());
        for(int i=arr.size()-1;i>=0;i--){
            while(!st.empty() && arr[st.top()]>=arr[i]){
                st.pop();
            }
            if(st.empty()){
                ans[i]=arr.size();
            }else{
                ans[i]=st.top();
            }
            st.push(i);
        }
        return ans;
    }
    
public:
    int largestRectangleArea(vector<int>&arr) {
        vector<int> nse= findnse(arr);
        vector<int> pse= findpse(arr);
        int n=arr.size();
        int maxi=0;
        for(int i=0;i<arr.size();i++){
            maxi=max(arr[i]*(nse[i]-pse[i]-1),maxi);
        }
        return maxi;
    }
};