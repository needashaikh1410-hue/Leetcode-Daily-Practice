class Solution {
private:
    void solve(int index, const string& num, long long target, 
               long long currentVal, long long prevVal, 
               string curr, vector<string>& ans){
        if(index==num.size()){
            if(currentVal==target){
            ans.push_back(curr);}
            return;
        }
        for(int i=index;i<num.size();i++){
            if(i>index && num[index]=='0'){
                break;
            }
            string part=num.substr(index,i-index+1);
            long long val=stoll(part);
            if(index==0){
                solve(i+1,num,target,val,val,part,ans);
            }
            else{
                solve(i+1,num,target,currentVal+val,val,curr+"+"+part,ans);
                solve(i+1,num,target,currentVal-val,-val,curr+"-"+part,ans);

                solve(i+1,num,target,currentVal - prevVal + (prevVal * val),prevVal*val,curr + "*" + part,ans);
            }
        }
    
    }
public:
    vector<string> addOperators(string num, int target) {
       vector<string> ans;
       if(num.empty()){
        return ans;
       } 
        solve(0, num, target, 0, 0, "", ans);
       return ans;
    }
};