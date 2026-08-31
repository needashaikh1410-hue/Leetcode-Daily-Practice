class Solution {
public:
    int maxScore(vector<int>& card, int k) {
        int rsum=0,lsum=0;
        int max_sum=0;
        for(int i=0;i<k;i++){
            lsum+=card[i];
        }
        max_sum=lsum;
        int rindex=card.size()-1;
        for(int i=k-1;i>=0;i--){
            lsum-=card[i];
            rsum+=card[rindex];
            rindex--;
            max_sum=max(max_sum,lsum+rsum);
        }
        return max_sum;
    }
};