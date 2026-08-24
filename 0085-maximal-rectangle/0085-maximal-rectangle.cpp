class Solution {
private:
    int largestRectangleArea(vector<int>& arr) {
        stack<int> st;
        int maxi = 0;
        int n = arr.size();

        for (int i = 0; i < n; i++) {
            while (!st.empty() && arr[st.top()] >= arr[i]) {
                int el = st.top();
                st.pop();
                int nse = i;
                int pse = st.empty() ? -1 : st.top();
                maxi = max(maxi, arr[el] * (nse - pse - 1));
            }
            st.push(i);
        }

        while (!st.empty()) {
            int nse = n;
            int el = st.top();
            st.pop();
            int pse = st.empty() ? -1 : st.top();
            maxi = max(maxi, arr[el] * (nse - pse - 1));
        }

        return maxi;
    }
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        int maxi=0;
        int n=matrix.size();
        int m=matrix[0].size();
        vector<int> height(m,0);
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(matrix[i][j]=='1'){
                    height[j]++;
                }
                else{
                    height[j]=0;
                }
            }
            int max_area=largestRectangleArea(height);
            maxi=max(maxi,max_area);
        }

        return maxi;
    }
};