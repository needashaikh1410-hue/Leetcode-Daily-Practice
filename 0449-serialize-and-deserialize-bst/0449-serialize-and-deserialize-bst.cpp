/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
public:

   
    string serialize(TreeNode* root) {
        if(root==nullptr){
            return "";
        }
        string ans="";
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty()){
            int siz=q.size();
            for(int i=0;i<siz;i++){
                TreeNode* curr=q.front();
                q.pop();
                if(curr==nullptr){
                    ans+="#,";
                }
                else{
                    ans+=to_string(curr->val)+",";
                    q.push(curr->left);
                    q.push(curr->right);

                }
            }
            
        }

        return ans;

    }

    TreeNode* deserialize(string data) {
        if(data.empty()){
            return nullptr;
        }
        stringstream ss(data);
        string str;

        getline(ss, str, ',');
        TreeNode* root = new TreeNode(stoi(str));
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty()){
            TreeNode* parent=q.front();
            q.pop();
            if(getline(ss, str, ',')){
                if(str=="#"){
                    parent->left=nullptr;
                }
                else{
                    TreeNode* leftnode=new TreeNode(stoi(str));
                    parent->left=leftnode;
                    q.push(leftnode);
                }
            }

            if(getline(ss, str, ',')){
                if(str=="#"){
                    parent->right=nullptr;
                }
                else{
                    TreeNode* rightnode=new TreeNode(stoi(str));
                    parent->right=rightnode;
                    q.push(rightnode);
                }
            }
        }
        return root;

    }
};

// Your Codec object will be instantiated and called as such:
// Codec* ser = new Codec();
// Codec* deser = new Codec();
// string tree = ser->serialize(root);
// TreeNode* ans = deser->deserialize(tree);
// return ans;