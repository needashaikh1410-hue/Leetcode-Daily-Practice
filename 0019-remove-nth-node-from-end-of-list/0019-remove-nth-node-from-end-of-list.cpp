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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        
        if(head==nullptr){
            return head;
        }
        int cnt=0;
        ListNode* temp=head;
        while(temp!=nullptr){
            temp=temp->next;
            cnt++;
        }
        if(n>cnt || n<=0){
            return head;
        }
        if(cnt==n){
            ListNode* new_head=head->next;
            ListNode* old_head=head;
            head=new_head;
            delete(old_head);
            return head;
        }
        
        int rem=cnt-n;
        temp=head;
        while(rem>1){
            rem--;
            temp=temp->next;
        }
        ListNode* del=temp->next;
        temp->next=temp->next->next;
        delete(del);
        return head;
    }
};