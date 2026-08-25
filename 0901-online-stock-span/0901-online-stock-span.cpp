class StockSpanner {
private:
vector<int> prices;
public:
    StockSpanner() {
        
    }
    
    int next(int price) {
        int span=0;
        prices.push_back(price);
        for(int i=prices.size()-1;i>=0;i--){
            if(prices[i]<=price){
                span++;
            }
            else{break;}
        }
        return span;
    }
};

/**
 * Your StockSpanner object will be instantiated and called as such:
 * StockSpanner* obj = new StockSpanner();
 * int param_1 = obj->next(price);
 */