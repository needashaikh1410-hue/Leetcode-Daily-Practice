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

public:
    ListNode* rotateRight(ListNode* head, int k) {

        if(head==nullptr || head->next==nullptr || k==0){
            return head;
        }
        ListNode* old_head=head;
        ListNode* temp=head;
        int cnt=1;
        while(temp->next!=nullptr){
            cnt++;
            temp=temp->next;
        }
        k=k%cnt;
        if(k==0){
            return head;
        }
        ListNode* tail=temp;
        int req=cnt-k-1;
        temp=head;
        while(req-- && temp!=nullptr){
            temp=temp->next;
        }
        ListNode* new_head=temp->next;
        temp->next=nullptr;
        tail->next=old_head;
        head=new_head;
        return head;
    }
};