/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *      TreeNode(int val) : val(val) , left(nullptr) , right(nullptr) {}
 * };
 **/

class Solution {
private:
    void inorder(TreeNode* root, vector<TreeNode*>& nodes) {
        if (root == nullptr) return;
        
        inorder(root->left, nodes);
        nodes.push_back(root); // Store raw node pointers in order
        inorder(root->right, nodes);
    }
public:
    void recoverTree(TreeNode* root) {
       vector<TreeNode*> nodes;
        inorder(root, nodes);

        TreeNode* first = nullptr;
        TreeNode* second = nullptr;

        // Find inversions directly by comparing node values in the pointer array
        for (int i = 0; i < nodes.size() - 1; i++) {
            if (nodes[i]->val > nodes[i + 1]->val) {
                if (first == nullptr) {
                    first = nodes[i];        // First violation element
                    second = nodes[i + 1];  // Candidate neighbor
                } else {
                    second = nodes[i + 1];  // Second violation element
                }
            }
        }

        // Swap the values directly at the memory locations
        if (first != nullptr && second != nullptr) {
            swap(first->val, second->val);
        }
    }
};