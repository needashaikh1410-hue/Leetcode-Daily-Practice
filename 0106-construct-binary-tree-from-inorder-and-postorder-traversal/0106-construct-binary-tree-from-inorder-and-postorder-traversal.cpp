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
TreeNode* build(vector<int>& inorder, int inStart,int inEnd,vector<int>& postorder,int postStart,int postEnd,unordered_map<int,int> &inmap){
    if(inStart>inEnd || postStart>postEnd){
        return nullptr;
    }
    TreeNode* root=new TreeNode(postorder[postEnd]);

    int index=inmap[root->val];
    int numsleft=index-inStart;

    root->left=build(inorder,inStart,index-1,postorder,postStart,postStart+numsleft-1,inmap);

    root->right=build(inorder,index+1,inEnd,postorder,postStart+numsleft,postEnd-1,inmap);

    return root;

}
public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        unordered_map<int,int> inmap;
        for(int i=0;i<inorder.size();i++){
            inmap[inorder[i]]=i;
        }
        return build(inorder,0,inorder.size()-1,postorder,0,postorder.size()-1,inmap);
    }
};