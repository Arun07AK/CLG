/*
class Node {
    int data;
    Node *next;

    Node(int x) {
        data = x;
        next = NULL;
    }
};
*/
class Solution {
  public:
    Node* deleteNode(Node* head, int key) {
        // code here
        if(head==nullptr)
        {
            return head;
        }
        if(head->data==key)
        {
            if(head->next == head) 
            {  // Single node case
                delete head;
                return nullptr;  // List is now empty
            }
            Node* p=head;
            while(p->next!=head)
            {
                p=p->next;
            }
            p->next=head->next;
            Node* temp=head;
            head=head->next;
            delete temp;
            return head;
            
        }
        else
        {
            Node* p=head;
            while(p->next!=head )
            {
                if(p->next->data==key)
                {
                    Node* temp;
                    temp=p->next;
                    p->next=p->next->next;
                    delete temp;
                    return head;
                }
                p=p->next;
                
            }
            return head;
        }
        
    }
};
