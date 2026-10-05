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
    int findMaxPath(TreeNode* root, int &maxi) {
        if (root == nullptr) {
            return 0;
        }

        // Ignore subtrees that contribute negative sums by clamping with max(0, ...)
        int leftlen = max(0, findMaxPath(root->left, maxi));
        int rightlen = max(0, findMaxPath(root->right, maxi));

        // Max path turning at current node
        maxi = max(maxi, leftlen + rightlen + root->val);

        // Return single maximum branch going downward to parent
        return root->val + max(leftlen, rightlen);
    }

public:
    int maxPathSum(TreeNode* root) {
        int maxi = INT_MIN; // Handles all-negative value trees
        findMaxPath(root, maxi);
        return maxi;
    }
};	