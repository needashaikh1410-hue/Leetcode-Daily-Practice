class KthLargest {
private:
int k;
priority_queue<int,vector<int>,greater<int>> pq;
public:
  KthLargest(int n, vector<int>& nums) {
    k=n;
    int siz=nums.size();
    for(int num:nums){
       add(num);
    }
  }

  int add(int val) {
    if(pq.size()<k){
        pq.push(val);
    }
    else{
        if(val>pq.top()){
            pq.pop();
            pq.push(val);
        }
    }
    return pq.top();
  }
};