# Remove Duplicates from Sorted List

## Problem Statement
Given the head of a sorted linked list, delete all duplicates such that each element appears only once. Return the linked list sorted as well.

**Examples:**
- Input: `[1,1,2]` → Output: `[1,2]`
- Input: `[1,1,2,3,3]` → Output: `[1,2,3]`

## Algorithm Approaches

### Optimal Approach: Single-Pointer (Remove-Next Strategy)

**Key Insight:** Always keep the current node, remove the next duplicate.

```cpp
ListNode* deleteDuplicates(ListNode* head) {
    if(head == nullptr) return head;
    
    ListNode* p = head;
    while(p->next) {
        if(p->val == p->next->val) {
            ListNode* dup = p->next;
            p->next = dup->next;
            delete dup;
            // Don't advance p - check for more consecutive duplicates
        } else {
            p = p->next;  // Only advance when no duplicate found
        }
    }
    return head;
}
```

**Why This Approach is Elegant:**
- **No head special cases needed** - head node is never deleted
- **Natural unification** - same logic works for head and middle duplicates
- **Simple pointer management** - only one traversal pointer needed

### Alternative: Two-Pointer (Remove-Current Strategy)

**Strategy:** Track previous and current, delete current when duplicate found.

```cpp
ListNode* deleteDuplicates(ListNode* head) {
    if(head == nullptr) return head;
    
    ListNode* prev = nullptr;
    ListNode* curr = head;
    
    while(curr && curr->next) {
        if(curr->val == curr->next->val) {
            ListNode* dup = curr->next;
            
            if(prev) {
                prev->next = dup;  // General case
            } else {
                head = dup;        // Head case - special handling needed
            }
            
            delete curr;
            curr = dup;
        } else {
            prev = curr;
            curr = curr->next;
        }
    }
    return head;
}
```

**Why This Requires Head Special Cases:**
- When deleting head node, no previous node exists to update
- Must directly modify head pointer
- More complex logic with if-else for head vs general cases

## Key Algorithm Design Insights

### Why Single-Pointer Approach Avoids Head Cases

**The magic is in the deletion strategy:**

```cpp
// Strategy: Keep current (p), delete next (p->next)
if(p->val == p->next->val) {
    delete p->next;  // Remove duplicate to the right
}
```

**Case Analysis:**

**Head duplicates `[1,1,2]`:**
```
p = head(1): Keep head(1), delete next(1)
Result: [1,2] - head pointer unchanged
```

**Middle duplicates `[1,2,2,3]`:**
```
p = node(1): No duplicate, advance
p = node(2): Keep node(2), delete next(2)  
Result: [1,2,3] - same logic as head case
```

**The unification works because:**
- Head node is never deleted in this strategy
- No head pointer updates needed
- Same operation pattern everywhere

### Consecutive Duplicates Handling

**Critical pattern for consecutive duplicates:**

```cpp
if(p->val == p->next->val) {
    // Remove duplicate
    delete dup;
    // DON'T advance p - stay and check for more duplicates
} else {
    p = p->next;  // Only advance when no duplicate found
}
```

**Example with `[1,1,1,2]`:**
```
p=node(1): Remove second 1 → [1,1,2]
p=node(1): Remove second 1 → [1,2]  
p=node(1): No duplicate, advance
p=node(2): End of list
```

## Common Implementation Bugs

### Bug 1: Wrong Pointer Assignment
```cpp
// Wrong
p->next = dup->next->next;  // Skips node after duplicate

// Correct  
p->next = dup->next;        // Connect to node after duplicate
```

### Bug 2: Always Advancing Pointer
```cpp
// Wrong - misses consecutive duplicates
if(p->val == p->next->val) {
    delete dup;
}
p = p->next;  // Always advances

// Correct - conditional advancement
if(p->val == p->next->val) {
    delete dup;
    // Stay at p to check for more duplicates
} else {
    p = p->next;  // Only advance when no duplicate
}
```

### Bug 3: Memory Leak
```cpp
// Wrong - no cleanup
p->next = dup->next;

// Correct - free memory
p->next = dup->next;
delete dup;
```

## Complexity Analysis

**Time Complexity:** O(n)
- Single pass through the list
- Each node visited once

**Space Complexity:** O(1)  
- Only uses constant extra space for pointers
- In-place modification

## Edge Cases Handled

1. **Empty list:** `head == nullptr` → return immediately
2. **Single node:** Loop doesn't run → return unchanged  
3. **No duplicates:** Traverses normally, no deletions
4. **All duplicates:** `[1,1,1,1]` → `[1]`
5. **Consecutive groups:** `[1,1,2,2,3,3]` → `[1,2,3]`

## Pattern Recognition: Three-Case Framework

**Traditional approach would handle:**
1. **Empty case:** `head == nullptr`
2. **Head case:** Special deletion logic for first node
3. **General case:** Standard two-pointer deletion

**Optimized approach unifies cases 2 and 3:**
1. **Empty case:** `head == nullptr` 
2. **Unified case:** Same logic for head and general duplicates

**Key insight:** Algorithm design choice (which node to delete) can eliminate special case complexity.

## Alternative Problem Variations

### Remove ALL Duplicates (Keep No Duplicates)
If the problem required removing ALL occurrences of duplicates:

```cpp
// Different algorithm needed - would require separate head handling
// Example: [1,1,2,3,3] → [2] (keep only unique elements)
```

### Unsorted List Duplicates  
For unsorted lists, would need different approach:
- Hash set to track seen values
- Or sort first, then apply this algorithm

## Professional Implementation Template

```cpp
/**
 * Remove duplicates from sorted linked list
 * @param head Pointer to head of sorted linked list
 * @return Modified head pointer (same as input for this algorithm)
 */
ListNode* deleteDuplicates(ListNode* head) {
    // Handle empty list
    if(head == nullptr) return head;
    
    ListNode* current = head;
    
    // Traverse and remove duplicates
    while(current->next != nullptr) {
        if(current->val == current->next->val) {
            // Found duplicate - remove next node
            ListNode* duplicate = current->next;
            current->next = duplicate->next;
            delete duplicate;
            // Don't advance - check for more consecutive duplicates
        } else {
            // No duplicate - advance to next unique element
            current = current->next;
        }
    }
    
    return head;
}
```

## Key Takeaways

1. **Strategy choice matters:** Remove-next vs remove-current affects complexity
2. **Sorted property enables optimization:** Adjacent comparison sufficient
3. **Conditional advancement:** Critical for consecutive duplicates
4. **Memory management:** Always delete removed nodes
5. **Algorithm unification:** Good design can eliminate special cases

This problem demonstrates how recognizing data structure properties (sorted order) and making smart algorithm design choices (which node to delete) can lead to elegant, simple solutions.
