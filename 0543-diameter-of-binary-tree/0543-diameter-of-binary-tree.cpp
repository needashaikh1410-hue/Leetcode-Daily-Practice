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
    int height(TreeNode* root,int & max_dia){
        if(root==nullptr){
            return 0;
        }
        int rightlen=height(root->left,max_dia);
        int leftlen=height(root->right,max_dia);
        max_dia=max(max_dia,rightlen+leftlen);
        return 1+max(rightlen,leftlen);
    }
public:
    int diameterOfBinaryTree(TreeNode* root) {
        if(root==nullptr){
            return 0;
        }
        int max_dia=0;
        height(root,max_dia);
        return max_dia;
    }
};