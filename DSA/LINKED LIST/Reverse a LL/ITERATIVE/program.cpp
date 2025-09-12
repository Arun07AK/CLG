/*
Definition of singly linked list:
struct ListNode
{
    int val;
    ListNode *next;
    ListNode()
    {
        val = 0;
        next = NULL;
    }
    ListNode(int data1)
    {
        val = data1;
        next = NULL;
    }
    ListNode(int data1, ListNode *next1)
    {
        val = data1;
        next = next1;
    }
};
*/

class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if(head==nullptr)
        {
            return head;
        }
        ListNode* p;
        p=head;
        ListNode* q;
        ListNode* where_next=nullptr;
        q=nullptr;
        
        while(p!=nullptr)
        {
            where_next=p->next;
            p->next=q;
            q=p;
            p=where_next;
        }
        return q;
        
    }
};
