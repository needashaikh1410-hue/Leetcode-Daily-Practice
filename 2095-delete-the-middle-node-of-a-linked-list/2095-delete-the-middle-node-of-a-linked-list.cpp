class Solution {
public:
    ListNode* deleteMiddle(ListNode* head) {
        if (head == nullptr || head->next == nullptr) {
            return nullptr;
        }
        int cnt=0;
        ListNode* temp=head;
        while(temp!=nullptr){
            cnt++;
            temp=temp->next;
        }
        int req=(cnt/2)-1;
        temp=head;
        for (int i = 0; i < req; i++) {
            temp = temp->next;
        }
        ListNode* del=temp->next;
        temp->next=temp->next->next;
        del->next = nullptr;
        delete (del);
        return head;
  }
};