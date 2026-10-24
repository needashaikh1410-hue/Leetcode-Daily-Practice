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
TreeNode* build(vector<int>& preorder,int preStart,int preEnd,vector<int>& inorder,int inStart,int inEnd,unordered_map<int,int>&inMap){
    if(preStart>preEnd || inStart>inEnd){
        return nullptr;
    }
    TreeNode* root=new TreeNode(preorder[preStart]);
    int inroot=inMap[root->val];
    int numsleft=inroot-inStart;
    root->left=build(preorder,preStart+1,preStart+numsleft,inorder,inStart,inroot-1,inMap);
    root->right=build(preorder,preStart+numsleft+1,preEnd,inorder,inroot+1,inEnd,inMap);
    return root;

}
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
    unordered_map<int,int>inMap;
        for(int i=0;i<inorder.size();i++){
            inMap[inorder[i]]=i;
        }
        return build(preorder,0,preorder.size()-1,inorder,0,inorder.size()-1,inMap);
    }
};