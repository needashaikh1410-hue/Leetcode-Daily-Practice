/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
private:
void markParents(TreeNode* root,unordered_map<TreeNode*,TreeNode*>&track_parent){
 queue<TreeNode*>q;
 q.push(root);
 while(!q.empty()){
    TreeNode* curr=q.front();
    q.pop();
    if(curr->left!=nullptr){
        q.push(curr->left);
        track_parent[curr->left]=curr;
    }
    if(curr->right!=nullptr){
        q.push(curr->right);
        track_parent[curr->right]=curr;
    }
 }
}
public:
	vector<int> distanceK(TreeNode* root, TreeNode* target, int k){
		unordered_map<TreeNode*,TreeNode*> track_parent;
        unordered_map<TreeNode*,bool> visited;
        markParents(root,track_parent);
        queue<TreeNode*>q;
        q.push(target);
        visited[target]=true;
        int curr_level=0;
        while(!q.empty()){
            int siz=q.size();
            if(curr_level==k){
                break;
            }
            curr_level++;
            for(int i=0;i<siz;i++){
                TreeNode* curr=q.front();
                q.pop();

                if(curr->left!=nullptr && !visited[curr->left]){
                    q.push(curr->left);
                    visited[curr->left]=true;
                }

                if(curr->right!=nullptr && !visited[curr->right]){
                    q.push(curr->right);
                    visited[curr->right]=true;
                }

                if(track_parent.find(curr)!=track_parent.end() && !visited[track_parent[curr]]){
                    visited[track_parent[curr]]=true;
                    q.push(track_parent[curr]);
                }
            }
        }

        vector<int> result;
        while(!q.empty()){
            result.push_back(q.front()->val);
            q.pop();
        }
        return result;
    }
};