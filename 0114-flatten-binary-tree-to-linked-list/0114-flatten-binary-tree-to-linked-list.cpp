/* class TreeNode {
       int val;
       TreeNode *left, *right;
       TreeNode(int x) : val(x), left(NULL), right(NULL) {}
   };
*/

class Solution {
private:
TreeNode* prev=nullptr;
public:
    void flatten(TreeNode* root) {
        if(root==nullptr){
            return;
        }
        flatten(root->right);
        flatten(root->left);
        root->left=nullptr;
        root->right=prev;
        prev=root;
    }
};
