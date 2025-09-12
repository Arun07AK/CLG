# Recursive Linked List Reversal

## Core Algorithm

```cpp
ListNode* reverseList(ListNode* head) {
    // Base case: empty list or single node
    if(head == nullptr || head->next == nullptr) {
        return head;
    }
    
    // Recursive case
    ListNode* newHead = reverseList(head->next);
    head->next->next = head;  // Attach current head as new tail
    head->next = nullptr;     // Make current head proper tail
    return newHead;           // Pass same newHead up the chain
}
```

## Key Insights

### Base Cases
- **Empty list** (`head == nullptr`): Return nullptr
- **Single node** (`head->next == nullptr`): Return the node (it's already "reversed")

### Recursive Pattern
At each recursive level (except base case):
1. **Trust recursion**: `reverseList(head->next)` returns the new head
2. **Local manipulation**: Attach current node as the new tail
3. **Pass through**: Return the same newHead received from recursion

### Critical Understanding
- **newHead identity**: The last node becomes newHead and NEVER changes throughout all recursive returns
- **Role transformation**: Each node transforms from "head of subproblem" to "tail of reversed subproblem"
- **Pointer insight**: After recursion, `head->next` points to the tail of the already-reversed portion

## Step-by-Step Flow

**Given: `1→2→3→4→NULL`**

### Recursion Down (Function Calls)
```
reverseList(1→2→3→4) → calls reverseList(2→3→4)
reverseList(2→3→4)   → calls reverseList(3→4)  
reverseList(3→4)     → calls reverseList(4)
reverseList(4)       → BASE CASE: return node(4)
```

### Recursion Up (Stack Unwinding)
```
Level 4: Return node(4)                    [newHead established]
Level 3: newHead=node(4), make 3→tail      [4→3→NULL]
Level 2: newHead=node(4), make 2→tail      [4→3→2→NULL]  
Level 1: newHead=node(4), make 1→tail      [4→3→2→1→NULL]
```

### Pointer Manipulation at Each Level
```cpp
head->next->next = head;  // Current head becomes tail of reversed portion
head->next = nullptr;     // Terminate the new tail properly
```

**Example at Level 2 (`reverseList(2→3→4)`):**
- Before: `2→3` with separate reversed portion `4→3→NULL`
- `head->next` (node 3) is now tail of reversed portion
- `node(3)->next = node(2)` attaches 2 as new tail
- `node(2)->next = nullptr` terminates properly
- After: `4→3→2→NULL`

## Visual Pattern

**Transformation at each recursive level:**
```
Before: head → [already_reversed_portion]
After:  [already_reversed_portion] → head → NULL
```

**Key insight**: Each node "moves" from being a head to being a tail as recursion unwinds.

## Complexity Analysis

- **Time Complexity**: O(n) - visit each node once
- **Space Complexity**: O(n) - recursive call stack depth equals list length

## Common Conceptual Mistakes

1. **Trying to return current head**: The current head becomes the tail, not the new head
2. **Forgetting tail termination**: Must set `head->next = nullptr`
3. **Misunderstanding newHead propagation**: The same newHead flows through all recursive returns
4. **Circular reference**: Without proper tail termination, creates infinite loops

## Recursive vs Iterative Comparison

| Aspect | Recursive | Iterative |
|--------|-----------|-----------|
| Space | O(n) call stack | O(1) extra space |
| Readability | More intuitive for some | More explicit pointer management |
| Debugging | Harder to trace | Easier to step through |
| Performance | Function call overhead | Direct pointer manipulation |

## Edge Cases Handled
- Empty list: Returns nullptr
- Single node: Returns unchanged  
- Two nodes: `1→2` becomes `2→1`
- Long lists: Pattern scales naturally

The recursive approach demonstrates how complex pointer manipulation can be elegantly expressed through recursive structure and the "trust the recursion" principle.
