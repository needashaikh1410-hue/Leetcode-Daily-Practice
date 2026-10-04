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
int height(TreeNode* root){
    if(root==nullptr){
        return 0;
    }
    int leftlen=height(root->left);
    if(leftlen==-1){return -1;}
    int rightlen=height(root->right);
    if(rightlen==-1){return -1;}
    if(abs(leftlen-rightlen)>1){
        return -1;
    }
    return 1+max(leftlen,rightlen);
}
public:
    bool isBalanced(TreeNode* root) {
        return height(root)!=-1;
    }
};