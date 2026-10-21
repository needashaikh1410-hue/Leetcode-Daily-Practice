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
struct NodeInfo {
        bool isBST;
        int minVal;
        int maxVal;
        int sum;
    };

    int maxSum = 0;
NodeInfo solve(TreeNode* root){
    if(!root){
        return{true ,INT_MAX ,INT_MIN ,0};
    }

    NodeInfo leftside=solve(root->left);
    NodeInfo rightside=solve(root->right);

    if(leftside.isBST && rightside.isBST && leftside.maxVal<root->val && rightside.minVal>root->val){
        int currsum=leftside.sum+rightside.sum+root->val;
        maxSum=max(maxSum,currsum);
        return {true,min(leftside.minVal,root->val),max(root->val,rightside.maxVal),currsum};
    }

    return {false,0,0,0};

}
public:
    int maxSumBST(TreeNode* root) {
        maxSum=0;
        solve(root);
        return maxSum;
    }
};