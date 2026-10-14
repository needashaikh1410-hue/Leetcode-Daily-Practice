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
class Solution {
public:
    int widthOfBinaryTree(TreeNode* root) {
        long long int ans=INT_MIN;
       if(root==nullptr){
        return 0;
       }
       queue<pair<TreeNode*,long long int>> q;
       q.push({root,0});
       while(!q.empty()){
        int siz=q.size();
        long long int mini=q.front().second;
        long long int maxi=q.back().second;
        ans=max(ans,maxi-mini+1);
        for(int i=0;i<siz;i++){
            long long int j=q.front().second-mini;
            TreeNode* node=q.front().first;
            q.pop();
            if(node->left!=nullptr){ q.push({node->left,2*j + 1 }); }
            if(node->right!=nullptr){  q.push({node->right,2*j + 2 });}
        }

       }
       return ans;
    }
};