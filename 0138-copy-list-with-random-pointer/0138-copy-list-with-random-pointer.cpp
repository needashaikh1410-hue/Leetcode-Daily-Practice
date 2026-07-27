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
private:
Node* addinbetween(Node* head){
    Node* temp=head;
    Node* prev=nullptr;
    while(temp!=nullptr){
        prev=temp->next;
        temp->next=new Node (temp->val);
        temp->next->next=prev;
        temp=temp->next->next;
    }
    return head;
}
Node* pointtorand(Node* head){
    Node* temp=head;
    while(temp!=nullptr){
        if (temp->random != nullptr) {
            temp->next->random = temp->random->next;
        }
        else{
            temp->next->random=nullptr;
        }
        temp=temp->next->next;
    }
    return head;
}
Node* makedeepcopy(Node* head){
    Node* dummy=new Node(-1);
    Node* res=dummy;
    Node* temp=head;
    while(temp!=nullptr){
        Node * copy=temp->next;
        Node* next_node=copy->next;
        res->next=copy;
        res=copy;
        temp->next=next_node;
        temp=next_node;
    }
    return  dummy->next;
}
public:
    Node* copyRandomList(Node* head) {
        if (!head) return nullptr;
        addinbetween(head);
        pointtorand(head);
        return makedeepcopy(head);
    }
};