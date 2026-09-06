class Solution {

public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int len=m+n;
        int gap=(len/2)+(len%2);
        while(gap>0){
            int left=0;
            int right=left+gap;
            while(right<len){
                //left in nums1 and roght in nums 2
                if(left<m && right>=m){
                    if(nums1[left]>nums2[right-m]){
                        swap(nums1[left],nums2[right-m]);
                    }
                }
                //both in nums1
                if(left<m && right<m){
                    if(nums1[left]>nums1[right]){
                        swap(nums1[left],nums1[right]);
                    }
                }
                //both in nums 2
                if(left>=m && right>=m){
                    if(nums2[left-m]>nums2[right-m]){
                        swap(nums2[left-m],nums2[right-m]);
                    }
                }
                right++;
                left++;
            }
            if (gap==1) break;
            gap=(gap/2)+(gap%2);
        }
        for(int i=0;i<n;i++){
            nums1[m+i]=nums2[i];
        }
    }
};