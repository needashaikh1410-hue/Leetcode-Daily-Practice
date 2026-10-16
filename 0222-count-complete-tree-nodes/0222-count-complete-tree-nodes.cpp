/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int data;
 *     TreeNode *left;
 *     TreeNode *right;
 *      TreeNode(int val) : data(val) , left(nullptr) , right(nullptr) {}
 * };
 **/

class Solution {
private:
int left_height(TreeNode* root){
    if(root==nullptr){
        return 0;
    }
    return 1+left_height(root->left);
}

int right_height(TreeNode* root){
    if(root==nullptr){
        return 0;
    }
    return 1+right_height(root->right);
}

public:
    int countNodes(TreeNode* root) { 
        if(root==nullptr){
            return 0;
        }
        int left_h=left_height(root);
        int right_h=right_height(root);
        if(left_h==right_h){
            return (1<<left_h )-1 ;
        }
        return 1 + countNodes(root->left) + countNodes(root->right);

    }
};