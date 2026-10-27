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
    TreeNode* searchBST(TreeNode* root, int target) {
        if(root==nullptr){
            return nullptr;
        }
    	TreeNode* curr=root;
        while(curr!=nullptr){
        if(target==curr->val){
            return curr;
        }
        if(target>curr->val){
            curr=curr->right;
        }
        else{
            curr=curr->left;
        }

        }
        return nullptr;
  
    }
};