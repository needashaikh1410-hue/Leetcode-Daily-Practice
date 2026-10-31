/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *      TreeNode(int val) : val(val) , left(nullptr) , right(nullptr) {}
 * };
 **/
class BSTIterator{
    private:
    stack<TreeNode*> st;
    bool isReverse;
    void pushleft(TreeNode* root){
        while(root!=nullptr){
            st.push(root);
            root=(isReverse)?root->right:root->left;
        }
    }
	public:
		BSTIterator(TreeNode* root,bool rev):isReverse(rev){
		    pushleft(root);
		}

		
		int next(){
            TreeNode* topnode=st.top();
            st.pop();
            if(!isReverse){
            if(topnode->right!=nullptr){
                pushleft(topnode->right);
            }}
            else{
                if(topnode->left!=nullptr){
                    pushleft(topnode->left);
            }}
            return topnode->val;
		}
};

class Solution{	
	public:
		bool findTarget(TreeNode* root, int k){
			if(root==nullptr){
                return false;
            }
            BSTIterator l(root,false);
            BSTIterator r(root,true);
            int i=l.next();
            int j=r.next();
            while(i<j){
                if(i+j==k){
                    return true;
                }
                else if(i+j>k){
                    j=r.next();
                }
                else{
                    i=l.next();
                }
            }
            return false;         
		}
};