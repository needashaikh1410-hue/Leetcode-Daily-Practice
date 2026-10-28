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
    TreeNode* insertIntoBST(TreeNode* root, int target) {
        if(root==nullptr){
            return new TreeNode(target);
        }
        TreeNode* curr=root;
        while(curr!=nullptr){
            if(target>curr->val){
                if(curr->right!=nullptr){
                    curr=curr->right;
                }
                else{
                    curr->right=new TreeNode(target);
                    break;
                }
            }
            else{
                if(curr->left!=nullptr){
                    curr=curr->left;
                }
                else{
                    curr->left=new TreeNode(target);
                    break;
                }
            }


        }

        return root;
    }
};