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
    TreeNode* findmin(TreeNode*root){
        while(root->left!=nullptr){
            root=root->left;
        }
        return root;
    }
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        if(root==nullptr){
            return nullptr;
        }
        if(key>root->val){
            root->right=deleteNode(root->right,key);
        }
        else if (key<root->val){
            root->left=deleteNode(root->left,key);
        }
        else{
            if(root->right==nullptr){
                TreeNode* temp=root->left;
                delete root;
                return temp;
            }
            else if(root->right==nullptr){
                TreeNode* temp=root->left;
                delete root;
                return temp;
            }

            TreeNode* successor=findmin(root->right);
            root->val=successor->val;
            root->right=deleteNode(root->right,successor->val);


        }
        return root;
    }
};