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
private:
    bool solve(TreeNode* root,TreeNode* maxi,TreeNode* mini){
        if(root==nullptr){
            return true;
        }

        if((maxi!=nullptr && root->val >=maxi->val) || (mini!=nullptr && root->val <= mini->val)){
            return false;
        }

        return solve(root->left,root,mini)&&
        solve(root->right,maxi,root);
    }
public:
    bool isValidBST(TreeNode* root) {
        if(root==nullptr){
            return true;
        }
       return solve(root,nullptr,nullptr) ;
    }
};