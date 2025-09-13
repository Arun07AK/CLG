   # Sorted Insert in Circular Linked List

## Problem
Insert a node in a sorted circular linked list while maintaining sorted order.

## Approach
Handle 3 cases:
1. **Empty list** - Create first node, make circular
2. **Insert at head** - New data < head data
3. **Insert elsewhere** - Find correct position

## Key Insights
- Always maintain circular property (`tail->next = head`)
- When inserting at head, update head pointer and connect tail to new head
- For middle/end insertion, find node where `current->next->data >= newData`

## Code
```cpp
Node* sortedInsert(Node* head, int data) {
    // Case 1: Empty list
    if(head == nullptr) {
        Node* temp = new Node(data);
        temp->next = temp;
        return temp;
    }
    
    // Case 2: Insert at beginning
    if(data < head->data) {
        Node* tail = head;
        while(tail->next != head) tail = tail->next;
        
        Node* newNode = new Node(data);
        newNode->next = head;
        tail->next = newNode;
        return newNode;  // New head
    }
    
    // Case 3: Insert in middle/end
    Node* curr = head;
    while(curr->next != head && curr->next->data < data) {
        curr = curr->next;
    }
    
    Node* newNode = new Node(data);
    newNode->next = curr->next;
    curr->next = newNode;
    return head;
}
