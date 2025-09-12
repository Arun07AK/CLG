// Definition of singly linked list:
// struct ListNode
// {
//     int val;
//     ListNode *next;
//     ListNode(int data1)
//     {
//         val = data1;
//         next = NULL;
//     }
//     ListNode(int data1, ListNode *next1)
//     {
//         val = data1;
//         next = next1;
//     }
// };

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        if(list1==nullptr)
        {
            return list2;
        }
        if(list2==nullptr)
        {
            return list1;
        }
        ListNode* p1;
        ListNode* p2;
        p1=list1;
        p2=list2;
        ListNode* p3;
        ListNode* last;
        
        if(p1->val<p2->val)
        {
            p3=p1;
            last=p1;
            p1=p1->next;
            last->next=nullptr;
        }
        else{
            p3=p2;
            last=p2;
            p2=p2->next;
            last->next=nullptr;
        }
        while(p1!=nullptr && p2!=nullptr)
        {
            if(p1->val<p2->val)
            {
                last->next=p1;
                last=p1;
                p1=p1->next;
                last->next=nullptr;
            }
            else{
                last->next=p2;
                last=p2;
                p2=p2->next;
                last->next=nullptr;
            }

        }
        if(p1!=nullptr)
        {
            last->next=p1;
            
        }
        if(p2!=nullptr)
        {
            last->next=p2;
            
        }
        return p3;
    }
};
