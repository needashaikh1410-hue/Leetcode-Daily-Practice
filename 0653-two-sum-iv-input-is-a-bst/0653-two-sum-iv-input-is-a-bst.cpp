/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *      TreeNode(int val) : val(val) , left(nullptr) , right(nullptr) {}
 * };
 **/

class Solution{	
    private:
        bool solve(TreeNode* root, int k, unordered_set<int>& st) {
        if (root == nullptr) {
            return false;
        }

        // 1. Search Left Subtree
        if (solve(root->left, k, st)) {
            return true;
        }

        // 2. Process Current Node (Check if complement (k - root->val) exists)
        if (st.find(k - root->val) != st.end()) {
            return true;
        }
        st.insert(root->val);

        // 3. Search Right Subtree
        return solve(root->right, k, st);
    }
	public:
		bool findTarget(TreeNode* root, int k){
            unordered_set<int> st;
        return solve(root, k, st);
		}
};