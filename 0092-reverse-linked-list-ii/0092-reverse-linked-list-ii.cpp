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
ListNode* reverseList(ListNode* head) {
        if(head==nullptr || head->next==nullptr){
           
            return head;
        }
        ListNode* new_head=reverseList(head->next);
        head->next->next=head;
        head->next=nullptr;
        return new_head;
    }
public:
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        if( !head || left==right){
            return head;
        }
        ListNode * dummy=new ListNode(0,head);
        ListNode * prev=dummy;
        
        ListNode*after=dummy;
        for(int i=0;i<right;i++){
            after=after->next;
        }
        for(int i=1;i<left;i++){
            prev=prev->next;
        }
        ListNode *subhead=prev->next;
        ListNode* subtail=after;
        after=after->next;
        subtail->next=nullptr;
        ListNode * rev=reverseList(subhead);
        prev->next=rev;
        subhead->next=after;
        ListNode *new_head=dummy->next;
        delete dummy;
        return new_head;
    }
};