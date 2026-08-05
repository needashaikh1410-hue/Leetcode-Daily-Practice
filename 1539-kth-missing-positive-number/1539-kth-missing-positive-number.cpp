class Solution {
public:
    int findKthPositive(vector<int>& arr, int k) {

        for(int num: arr){
            if(k>=num){
                k++;
            }
            else{
                break;
            }
        }
        return k;
    }
};