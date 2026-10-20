/* class TreeNode {
       int val;
       TreeNode *left, *right;
       TreeNode(int x) : val(x), left(NULL), right(NULL) {}
   };
*/

class Solution {
public:
    void flatten(TreeNode* root) {
        if(root==nullptr){
            return;
        }
        stack<TreeNode*> st;
        st.push(root);
        while(!st.empty()){
            TreeNode* curr=st.top();
            st.pop();
            if(curr->right!=nullptr){
                st.push(curr->right);
            }
            if(curr->left!=nullptr){
                st.push(curr->left);
            }
            if(!st.empty()){
                curr->left=nullptr;
                curr->right=st.top();
            }
        }

    }
};
