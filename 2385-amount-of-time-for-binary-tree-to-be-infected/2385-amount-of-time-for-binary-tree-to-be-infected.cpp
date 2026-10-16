/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution{
    private:
TreeNode* markParents(TreeNode* root,unordered_map<TreeNode*,TreeNode*>&track_parent,int target){
 TreeNode* targetNode=nullptr;
 queue<TreeNode*>q;
 q.push(root);
 while(!q.empty()){
    TreeNode* curr=q.front();
    q.pop();
    if(curr->val==target){
        targetNode=curr;
    }
    if(curr->left!=nullptr){
        q.push(curr->left);
        track_parent[curr->left]=curr;
    }
    if(curr->right!=nullptr){
        q.push(curr->right);
        track_parent[curr->right]=curr;
    }
 }
 return targetNode;
}

	public:
		int amountOfTime(TreeNode* root, int start){
            unordered_map<TreeNode*,TreeNode*> track_parent;
        unordered_map<TreeNode*,bool> visited;
        TreeNode* target=markParents(root,track_parent,start);
        queue<TreeNode*>q;
        q.push(target);
        visited[target]=true;
        int curr_level=0;
        while(!q.empty()){
            bool flag=false;
            int siz=q.size();

            for(int i=0;i<siz;i++){
                
                TreeNode* curr=q.front();
                q.pop();

                if(curr->left!=nullptr && !visited[curr->left]){
                    flag=true;
                    q.push(curr->left);
                    visited[curr->left]=true;
                }

                if(curr->right!=nullptr && !visited[curr->right]){
                    flag=true;
                    q.push(curr->right);
                    visited[curr->right]=true;
                }

                if(track_parent.find(curr)!=track_parent.end() && !visited[track_parent[curr]]){
                    flag=true;
                    visited[track_parent[curr]]=true;
                    q.push(track_parent[curr]);
                }
                
            }
            if(flag){
                curr_level++;
            }
        }

        return curr_level;
		}	
};