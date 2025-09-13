/* structure for a node
class Node {
 public:
  int data;
  Node *next;

  Node(int x){
      data = x;
      next = NULL;
  }
}; */

class Solution {
  public:
    Node* sortedInsert(Node* head, int data) {
        // code here
        //headcase+emptycase 
        if(head==nullptr)
            {
                Node* temp= new Node(data);
                head=temp;
                head->next=head;
                return head;
            }
        if(data<head->data)
        {
            Node* p=head;
            while(p->next!=head)
            {
                p=p->next;
            }
            Node* temp= new Node(data);
            temp->next=p->next;
            p->next=temp;
            head=temp;
            return head;
            
        }
        else{
            Node* p=head;
            while(p->next != head && p->next->data < data) 
            {
                p = p->next;
            }
            Node* temp= new Node(data);
            temp->next=p->next;
            p->next=temp;
            
        }
        
        
        return head;
        //gencase 
    }
};
