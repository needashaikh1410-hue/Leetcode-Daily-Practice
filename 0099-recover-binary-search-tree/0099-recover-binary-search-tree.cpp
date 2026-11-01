/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *      TreeNode(int val) : val(val) , left(nullptr) , right(nullptr) {}
 * };
 **/

class Solution {
private:
TreeNode* prev;
TreeNode* first;
TreeNode* middle;
TreeNode* last;
void inorder(TreeNode* root){
    if(root==nullptr){
        return ;
    }
    inorder(root->left);
    if(prev!=nullptr && root->val<prev->val){
        if(first==nullptr){
            first=prev;
            middle=root;
        }
        else{
            last=root;
        }
    }
    prev=root;
    inorder(root->right);
}
public:
    void recoverTree(TreeNode* root) {
       first=nullptr,last=nullptr,prev=nullptr,middle=nullptr;
       inorder(root);
       if(first!=nullptr && last!=nullptr){
            swap(first->val,last->val);
       }
       else if(first!=nullptr && middle!=nullptr){
            swap(first->val,middle->val);
       } 
    }
};