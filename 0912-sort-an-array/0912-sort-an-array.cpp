class Solution {
void heapify_down(vector<int> &heap,int n,int ind){
    
    while(true){
        int left=2*ind+1;
        int right=2*ind+2;
        int largest=ind;

        if(left<n && heap[left]>heap[largest]){
            largest=left;
        }
        
        if(right<n && heap[right]>heap[largest]){
            largest=right;
        }

        if(largest!=ind){
            swap(heap[ind],heap[largest]);
            ind=largest;
        }
        else{
            break;
        }
    }
    

}

public:
    vector<int> sortArray(vector<int>& nums) {
        int n=nums.size();
        for(int i=(n/2)-1;i>=0;i--){
            heapify_down(nums,n,i);
        }
        for(int i=n-1;i>0;i--){
            swap(nums[0],nums[i]);
            heapify_down(nums,i,0);
        }

        return nums;
    }
};