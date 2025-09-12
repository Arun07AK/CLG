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
    bool hasCycle(ListNode *head) {
        ListNode* p;
        ListNode* q;
        p=head;
        q=head;
        while(q!=nullptr && q->next!=nullptr)
        {
            
            p=p->next;
            q=q->next->next;
            if(p==q)
            {
                return true;   
            }
        }
        return false ;

    }
};
