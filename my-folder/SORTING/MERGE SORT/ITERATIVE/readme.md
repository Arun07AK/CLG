# Merge Sort

## Algorithm Overview

**Core Philosophy:** "Divide and Conquer - Split until trivial, then build solution bottom-up"

Merge Sort is a stable, divide-and-conquer sorting algorithm that works by recursively splitting the array into smaller subarrays until each subarray contains a single element, then merging these subarrays back together in sorted order.

## Algorithm Steps

1. **Divide:** Split the array into two halves at the middle point
2. **Conquer:** Recursively sort both halves
3. **Combine:** Merge the two sorted halves into a single sorted array
4. **Base Case:** Single element arrays are already sorted

## Recursive Implementation (Top-Down Approach)

```cpp
class Solution {
public:
    vector<int> mergeSort(vector<int>& nums) {
        if (nums.empty()) return nums;
        mergeSortHelper(nums, 0, nums.size() - 1);
        return nums;
    }
    
private:
    void mergeSortHelper(vector<int>& nums, int low, int high) {
        // Base case: single element or empty subarray
        if (low >= high) {
            return;
        }
        
        // Divide: Find the middle point
        int mid = low + (high - low) / 2;  // Avoid overflow
        
        // Conquer: Recursively sort both halves
        mergeSortHelper(nums, low, mid);         // Sort left half
        mergeSortHelper(nums, mid + 1, high);   // Sort right half
        
        // Combine: Merge the sorted halves
        merge(nums, low, mid, high);
    }
    
    void merge(vector<int>& nums, int low, int mid, int high) {
        // Create temporary array to store merged result
        vector<int> temp;
        
        // Pointers for left and right subarrays
        int left = low;      // Start of left subarray
        int right = mid + 1; // Start of right subarray
        
        // Merge two sorted subarrays
        while (left <= mid && right <= high) {
            if (nums[left] <= nums[right]) {
                temp.push_back(nums[left]);
                left++;
            } else {
                temp.push_back(nums[right]);
                right++;
            }
        }
        
        // Add remaining elements from left subarray
        while (left <= mid) {
            temp.push_back(nums[left]);
            left++;
        }
        
        // Add remaining elements from right subarray
        while (right <= high) {
            temp.push_back(nums[right]);
            right++;
        }
        
        // Copy merged elements back to original array
        for (int i = 0; i < temp.size(); i++) {
            nums[low + i] = temp[i];
        }
    }
};
```

## Iterative Implementation (Bottom-Up Approach)

```cpp
class Solution {
public:
    void mergeSort(vector<int>& arr, int l, int r) {
        int n = arr.size();
        
        // Process subarray sizes: 1, 2, 4, 8, 16...
        for (int size = 1; size < n; size *= 2) {
            
            // Find all pairs of subarrays of current size
            for (int left = 0; left < n; left += 2 * size) {
                
                // Calculate boundaries with safety checks
                int mid = min(left + size - 1, n - 1);     // End of left subarray
                int high = min(left + 2 * size - 1, n - 1); // End of right subarray
                
                // Only merge if right subarray exists
                if (mid < high) {
                    merge(arr, left, mid, high);
                }
            }
        }
    }
    
    // Same merge function as recursive version
    void merge(vector<int>& nums, int low, int mid, int high) {
        vector<int> temp;
        int left = low;
        int right = mid + 1;
        
        while (left <= mid && right <= high) {
            if (nums[left] <= nums[right]) {
                temp.push_back(nums[left]);
                left++;
            } else {
                temp.push_back(nums[right]);
                right++;
            }
        }
        
        while (left <= mid) {
            temp.push_back(nums[left]);
            left++;
        }
        
        while (right <= high) {
            temp.push_back(nums[right]);
            right++;
        }
        
        for (int i = 0; i < temp.size(); i++) {
            nums[low + i] = temp[i];
        }
    }
};
```

## Iterative Implementation Deep Dive

### Core Logic Explained

**The Two-Loop Strategy:**
1. **Outer Loop:** Controls subarray size being merged (1, 2, 4, 8...)
2. **Inner Loop:** Finds all pairs of subarrays of current size

### Step-by-Step Trace

**Array:** `[8, 3, 5, 4, 7, 6]` (n = 6)

#### **size = 1** (merge single elements):
```
left = 0: mid = 0, high = 1 → merge([8], [3]) → [3, 8]
left = 2: mid = 2, high = 3 → merge([5], [4]) → [4, 5]  
left = 4: mid = 4, high = 5 → merge([7], [6]) → [6, 7]
left = 6: Exit (6 >= 6)

Result: [3, 8, 4, 5, 6, 7]
```

#### **size = 2** (merge pairs):
```
left = 0: mid = 1, high = 3 → merge([3,8], [4,5]) → [3,4,5,8]
left = 4: mid = 5, high = 5 → Skip (5 not < 5, no right subarray)
left = 8: Exit (8 >= 6)

Result: [3, 4, 5, 8, 6, 7]
```

#### **size = 4** (merge groups of 4):
```
left = 0: mid = 3, high = 5 → merge([3,4,5,8], [6,7]) → [3,4,5,6,7,8]
left = 8: Exit (8 >= 6)

Result: [3, 4, 5, 6, 7, 8] ✅ SORTED!
```

### Key Components Explained

#### **1. Why `left += 2 * size`?**
```cpp
// After merging two subarrays of size `size`:
[size_elements] + [size_elements] = [2*size_elements]
//                                     ↑
//                              Skip over merged block
//                              Next pair starts at: left + 2*size
```

#### **2. Why `min(left + size - 1, n - 1)`?**
**Purpose:** Find where left subarray ends safely

**Example:** Array size 5, left = 3, size = 4
```cpp
// Without min(): 3 + 4 - 1 = 6 ❌ (Index 6 doesn't exist!)
// With min(): min(6, 4) = 4 ✅ (Capped at last valid index)
```

#### **3. Why `min(left + 2*size - 1, n - 1)`?**
**Purpose:** Find where right subarray ends safely

**Example:** Array size 3, left = 0, size = 4  
```cpp
// Without min(): 0 + 8 - 1 = 7 ❌ (Index 7 doesn't exist!)
// With min(): min(7, 2) = 2 ✅ (Capped at last valid index)
```

#### **4. Why `if (mid < high)`?**
**Purpose:** Only merge when right subarray actually exists

```cpp
// mid < high: Right subarray = [mid+1...high] has elements → Valid merge
// mid = high: Right subarray = [mid+1...mid] is empty → Skip merge  
```

## Visual Trace Example (Recursive)

**Array:** `[8, 3, 5, 4, 7, 6, 1, 2]`

### Splitting Phase (Divide):
```
                    [8, 3, 5, 4, 7, 6, 1, 2]
                            ↓ SPLIT
                [8, 3, 5, 4]          [7, 6, 1, 2]
                     ↓ SPLIT               ↓ SPLIT
             [8, 3]     [5, 4]     [7, 6]     [1, 2]
              ↓ SPLIT    ↓ SPLIT    ↓ SPLIT    ↓ SPLIT
           [8]  [3]   [5]  [4]   [7]  [6]   [1]  [2]
           ↑    ↑     ↑    ↑     ↑    ↑     ↑    ↑
        BASE CASE - Single elements (already sorted)
```

### Merging Phase (Combine):
```
Level 1: Merge adjacent single elements
         [8] + [3] → [3, 8]
         [5] + [4] → [4, 5]  
         [7] + [6] → [6, 7]
         [1] + [2] → [1, 2]

Level 2: Merge pairs of sorted arrays  
         [3, 8] + [4, 5] → [3, 4, 5, 8]
         [6, 7] + [1, 2] → [1, 2, 6, 7]

Level 3: Final merge
         [3, 4, 5, 8] + [1, 2, 6, 7] → [1, 2, 3, 4, 5, 6, 7, 8]
```

## Complexity Analysis

### Time Complexity
- **All Cases:** O(n log n) - **Guaranteed!**

**Why O(n log n)?**
- **Levels:** log n (array gets halved each recursion level)
- **Work per level:** O(n) (each element processed once per level)
- **Total:** O(n) × O(log n) = O(n log n)

### Space Complexity
- **Auxiliary Space:** O(n) - Temporary arrays for merging
- **Call Stack:** O(log n) - Recursion depth  
- **Total:** O(n)

## Algorithm Properties

### ✅ Stable
Preserves relative order of equal elements.

**Example:**
```
Input:  [4a, 2, 4b, 1]  
Output: [1, 2, 4a, 4b]  ✅ 4a still comes before 4b
```

**Why stable:** `nums[left] <= nums[right]` ensures left elements come first when equal.

### ❌ Not Adaptive  
Performs same work regardless of input order.
- Sorted array: O(n log n)
- Random array: O(n log n)  
- Reverse sorted: O(n log n)

### ❌ Not In-Place
Requires O(n) extra space for temporary arrays.

### ✅ Predictable Performance
Always O(n log n) - no worst-case surprises.

## Recursive vs Iterative Comparison

| Aspect | **Recursive (Top-Down)** | **Iterative (Bottom-Up)** |
|--------|---------------------------|----------------------------|
| **Conceptual Model** | Split until trivial, merge up | Start with singles, merge up |
| **Space Complexity** | O(n + log n) | O(n) |
| **Implementation** | More intuitive | Slightly more complex |
| **Function Calls** | O(log n) calls | No recursion overhead |
| **Debugging** | Easier to trace | Requires careful boundary logic |

## When to Use Merge Sort

### ✅ Use Merge Sort When:
- **Stability required** - Need to preserve order of equal elements
- **Guaranteed performance** - Must have O(n log n) in all cases
- **Large datasets** - Consistent performance regardless of input
- **External sorting** - Can handle data larger than memory
- **Linked list sorting** - Natural fit for linked structures

### ❌ Avoid Merge Sort When:
- **Memory constrained** - O(n) extra space is prohibitive
- **Small arrays** - Overhead not worth it (use insertion sort)
- **In-place sorting required** - Use heap sort or quicksort
- **Cache performance critical** - Quicksort often performs better

## Common Mistakes and Solutions

### 1. **Infinite Loop in Merge**
```cpp
// ❌ WRONG - Missing equal case
if (nums[left] < nums[right]) {
    // ...left++
} else if (nums[left] > nums[right]) {
    // ...right++
}
// If equal, neither advances → infinite loop!

// ✅ CORRECT
if (nums[left] <= nums[right]) {
    temp.push_back(nums[left]);
    left++;
} else {
    temp.push_back(nums[right]);
    right++;
}
```

### 2. **Array Copy-Back Errors**
```cpp
// ❌ WRONG - Always copies to start
for (int i = 0; i < temp.size(); i++) {
    nums[i] = temp[i];  // Wrong positions!
}

// ✅ CORRECT - Copy to subarray positions
for (int i = 0; i < temp.size(); i++) {
    nums[low + i] = temp[i];  // Correct positions!
}
```

### 3. **Boundary Calculation Errors**
```cpp
// ❌ DANGEROUS - No bounds checking
int mid = left + size - 1;
int high = left + 2 * size - 1;

// ✅ SAFE - Prevent out-of-bounds access
int mid = min(left + size - 1, n - 1);
int high = min(left + 2 * size - 1, n - 1);
```

## Pattern Recognition for LeetCode

Merge Sort concepts appear in many problems:

### 1. **Merge Two Sorted Arrays** (Direct Application)
```cpp
// Uses the exact merge logic from merge sort
void merge(vector<int>& nums1, vector<int>& nums2);
```

### 2. **Count Inversions** (Modified Merge Sort)
```cpp
// Count pairs where i < j but nums[i] > nums[j]
// Modify merge process to count while merging
```

### 3. **Sort List** (Linked List Merge Sort)
```cpp
// Perfect for linked lists - no extra space needed for arrays
ListNode* mergeSort(ListNode* head);
```

### 4. **Reverse Pairs** (Enhanced Merge Sort)
```cpp
// Count pairs where nums[i] > 2 * nums[j] and i < j
// Use merge sort with counting during merge phase
```

## Real-World Applications

- **Java Collections.sort()** (for objects - stability required)
- **Python's sorted()** and **Timsort** (hybrid with merge sort)  
- **Database sorting operations** (external sorting for large datasets)
- **Version control systems** (merging file changes)
- **Graphics processing** (sorting primitives by z-order)

## Key Takeaways

### **Algorithm Design Insights:**
1. **Divide-and-conquer** creates naturally balanced subproblems
2. **Bottom-up approach** can eliminate recursion overhead
3. **Boundary checking** prevents crashes and handles edge cases
4. **Stable merging** preserves relative order of equal elements

### **Implementation Mastery:**
- **Master the merge operation** - it's the core of the algorithm
- **Handle edge cases gracefully** - empty subarrays, boundary conditions
- **Choose approach wisely** - recursive for clarity, iterative for efficiency
- **Apply boundary safety** - always use min() for array bounds

### **Pattern Recognition:**
- **Two-pointer merge technique** applies to many problems
- **Divide-and-conquer structure** useful beyond sorting
- **Stability property** crucial for maintaining data relationships
- **External sorting principles** important for big data processing

**Merge Sort represents algorithmic elegance** - guaranteed performance, stable behavior, and clean divide-and-conquer design make it a fundamental algorithm that every programmer should master deeply.

---

**Remember:** Merge sort's true strength lies in its **reliability and predictability** - it may not always be the fastest sort, but it's the sort you can always count on to perform consistently well, regardless of input characteristics.
