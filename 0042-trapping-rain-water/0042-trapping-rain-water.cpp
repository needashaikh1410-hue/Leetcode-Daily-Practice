class Solution {
public:
    int trap(vector<int>& height) {
        vector<int> prefix(height.size()) ;
        vector<int> suffix(height.size()) ;
        int n=height.size();
        prefix[0]=height[0];
        suffix[n-1]=height[n-1];
        for(int i=1;i<n;i++){
            prefix[i]=max(prefix[i-1],height[i]);
        }
        for(int i=n-2;i>=0;i--){
            suffix[i]=max(suffix[i+1],height[i]);
        }
        int total=0;
        for(int i=0;i<n;i++){
            int leftmax=prefix[i];
            int rightmax=suffix[i];
            total+=min(leftmax,rightmax)-height[i];
    
        }
        return total;

    }

}; 