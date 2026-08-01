class Solution {
private:
    bool dfs(vector<vector<char>>& board, string word,int r,int c,int index){
        if(index==word.size()){
            return true;
        }
        int m=board.size();
        int n=board[0].size();

        if(r<0 || c<0 || r>=m|| c>=n || board[r][c]!=word[index]){
            return false;
        }
        char temp=board[r][c];
        board[r][c]='#';

        bool found=dfs(board,word,r+1,c,index+1)||
        dfs(board,word,r-1,c,index+1)||
        dfs(board,word,r,c-1,index+1)||
        dfs(board,word,r,c+1,index+1);

        board[r][c]=temp;
        return found;
    }
public:
    bool exist(vector<vector<char>>& board, string word) {
        int m=board.size();
        int n=board[0].size();

        for(int r=0;r<m;r++){
            for(int c=0;c<n;c++){
                if(dfs(board,word,r,c,0)){
                    return true;
                }
            }
        }
        return false;
    }
};