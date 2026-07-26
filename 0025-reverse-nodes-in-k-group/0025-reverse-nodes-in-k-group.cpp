/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
private:
    ListNode* find_kth(ListNode* head,int k){
        k-=1;
        ListNode* temp=head;
        while(k-- && temp!=nullptr){
            temp=temp->next;
        }
        return temp;
    }
    ListNode* reversell(ListNode* head){
        ListNode* temp=head;
        if(temp==nullptr||temp->next==nullptr){
            return temp;
        }
        ListNode* new_head=reversell(head->next);
        temp->next->next=temp;
        temp->next=nullptr;
        return new_head;
    }
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode*temp=head;
        ListNode* prev=nullptr;
        while(temp!=nullptr){
            ListNode* kth=find_kth(temp,k);
            if(kth==nullptr){
                if(prev){
                    prev->next=temp;
                }
                break;}
                ListNode* next_node=kth->next;
                kth->next=nullptr;
                reversell(temp);
                if(temp==head){
                    head=kth;
                }
                else{
                    prev->next=kth;
                }
                prev=temp;
                temp=next_node;
        } 
         return head;
    }
};