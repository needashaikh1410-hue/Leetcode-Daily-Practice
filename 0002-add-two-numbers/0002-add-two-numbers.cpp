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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* temp1=l1;
        ListNode* temp2=l2;
        ListNode* dummy=new ListNode(-1); 
        ListNode* ans=dummy;
        int carry=0;
        while(temp1!=nullptr || temp2!=nullptr){
            int sum=carry;
            if(temp1){sum+=temp1->val;
            temp1=temp1->next;}
            if(temp2){sum+=temp2->val;
            temp2=temp2->next;}
            if(sum>=10){
                sum=sum%10;
                carry=1;
            }
            else{
                carry=0;
            }
            ListNode* temp=new ListNode (sum);
            ans->next=temp;
            ans=ans->next;
        }
        if(carry==1){
            ans->next=new ListNode (1);
        }
        return dummy->next;
    }
};