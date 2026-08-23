class Solution {
public:
    int largestRectangleArea(vector<int>& arr) {
      stack<int> st;
      int maxi=0;
      int n=arr.size();
      for(int i=0;i<n;i++){
        while(!st.empty() && arr[st.top()]>=arr[i]){
            int el=st.top();
            st.pop();
            int nse=i;
            int pse=st.empty()? -1 :st.top(); 
            maxi=max(maxi,arr[el]*(nse-pse-1));
        }
        st.push(i);
      }  
      while(!st.empty()){
            int nse=n;
            int el=st.top();
            st.pop();
            int pse=st.empty()? -1 :st.top(); 
            maxi=max(maxi,arr[el]*(nse-pse-1));
        }
      return maxi;
    }
};