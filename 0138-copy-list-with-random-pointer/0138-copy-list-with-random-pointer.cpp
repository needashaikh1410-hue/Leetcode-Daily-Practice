/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/

class Solution {
public:
    Node* copyRandomList(Node* head) {
        if(head){
        Node* temp=head;
        unordered_map<Node*,Node*> mpp;
        while(temp!=nullptr){
            Node* new_node=new Node(temp->val);
            mpp[temp]=new_node;
            temp=temp->next;
        }
        temp=head;
        Node* new_head=mpp[temp];
        while(temp!=nullptr){
            Node * new_node=mpp[temp];
            new_node->next=mpp[temp->next];
            new_node->random=mpp[temp->random];
            temp=temp->next;
        }
        return new_head;
        }
        return nullptr;
    }   
};