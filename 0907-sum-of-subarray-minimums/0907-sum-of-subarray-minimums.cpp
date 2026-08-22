class Solution {
private:
    vector<int> findnse(vector<int>& arr){
        vector<int> nse(arr.size());
        stack <int> st;
        for(int i=arr.size()-1;i>=0;i--){
            while(!st.empty() && arr[st.top()]>=arr[i]){
                st.pop();
            }
            nse[i]= st.empty()?arr.size():st.top();
            st.push(i);
        }
        return nse;

    } 
vector<int> findpsee(vector<int>& arr){
        vector<int> psee(arr.size());
        stack <int> st;
        for(int i=0;i<arr.size();i++){
            while(!st.empty() && arr[st.top()]>arr[i]){
                st.pop();
            }
            psee[i]= st.empty()?-1:st.top();
            st.push(i);
        }
        return psee;
    } 
public:
    int sumSubarrayMins(vector<int>& arr) {
        int mod=(int)(1e9+7);
        vector<int> psee=findpsee(arr);
        vector<int> nse=findnse(arr);
        long long total = 0;
        for(int i=0;i<arr.size();i++){
            
            long long left = i - psee[i];
            long long right = nse[i] - i;

            long long freq = (left * right) % mod;
            long long val = (freq * arr[i]) % mod;
            total = (total + val) % mod;
            }
        return total;
    }
};