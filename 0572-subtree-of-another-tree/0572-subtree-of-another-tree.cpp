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
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if(p==nullptr && q==nullptr){
            return true;
        }
        if(p==nullptr || q==nullptr){
            return false;
        }
        if(p->val!=q->val){
            return false;
        }
        return isSameTree(p->left,q->left) && isSameTree(p->right,q->right) ;   
    }
public:
    bool isSubtree(TreeNode* root, TreeNode* subroot) {
        if(subroot==nullptr){
            return false;
        }
        if(root==nullptr){
            return false;
        }
        if(isSameTree(root,subroot)){
            return true;
        }
        return isSubtree(root->left,subroot) || isSubtree(root->right,subroot);
    }
};