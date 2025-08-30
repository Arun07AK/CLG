# Merge Sort

## Algorithm Overview

**Core Philosophy:** "Divide and Conquer - Split until trivial, then build solution bottom-up"

Merge Sort is a stable, divide-and-conquer sorting algorithm that works by recursively splitting the array into smaller subarrays until each subarray contains a single element, then merging these subarrays back together in sorted order.

## Algorithm Steps

1. **Divide:** Split the array into two halves at the middle point
2. **Conquer:** Recursively sort both halves
3. **Combine:** Merge the two sorted halves into a single sorted array
4. **Base Case:** Single element arrays are already sorted

## Core Pattern: Recursive Structure

**Key Insight:** Unlike quicksort where work happens before recursion, merge sort does work AFTER recursion (during the "return journey").

```
MergeSort Pattern:
1. DIVIDE first (just mathematical split)
2. RECURSE on smaller pieces  
3. MERGE while returning (do the real work here)
```

## Complete Implementation

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

## Visual Trace Example

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

## Detailed Merge Process Example

**Merging `[3, 8]` and `[4, 5]`:**

```
Step 1: Compare 3 and 4 → 3 ≤ 4, take 3
        temp = [3], left moves to 8

Step 2: Compare 8 and 4 → 8 > 4, take 4  
        temp = [3, 4], right moves to 5

Step 3: Compare 8 and 5 → 8 > 5, take 5
        temp = [3, 4, 5], right exhausted

Step 4: Add remaining left elements
        temp = [3, 4, 5, 8]

Step 5: Copy back to original array positions
```

## Complexity Analysis

### Time Complexity
- **All Cases:** O(n log n) - **Guaranteed!**

**Detailed Analysis:**
- **Splitting:** O(log n) levels (divide by 2 each time)
- **Merging:** O(n) work per level (each element visited once per level)
- **Total:** O(n) × O(log n) = O(n log n)

**Why it's guaranteed O(n log n):**
- Always splits in half regardless of input
- No worst-case scenario like quicksort

### Space Complexity
- **Auxiliary Space:** O(n) - Temporary arrays for merging
- **Call Stack:** O(log n) - Recursion depth
- **Total:** O(n)

## Algorithm Properties

### ✅ Stable
Merge sort **preserves** the relative order of equal elements.

**Example:**
```
Input:  [4a, 2, 4b, 1]  
Output: [1, 2, 4a, 4b]  ✅ 4a still comes before 4b
```

**Why stable:** When elements are equal, we always take from the left array first (`nums[left] <= nums[right]`).

### ❌ Not Adaptive  
Merge sort performs the **same work** regardless of input order.

- Sorted array: O(n log n)
- Random array: O(n log n)  
- Reverse sorted: O(n log n)

**Why not adaptive:** Always splits to single elements and merges back up, regardless of existing order.

### ❌ Not In-Place
Requires O(n) extra space for temporary arrays during merging.

### ✅ Predictable Performance
**Always** O(n log n) - no worst-case surprises like quicksort.

## Comparison with Other Divide-and-Conquer Sorts

### Merge Sort vs Quick Sort

| Aspect | **Merge Sort** | **Quick Sort** |
|--------|----------------|----------------|
| **When work happens** | **After recursion** | **Before recursion** |
| **Guaranteed time** | O(n log n) ✅ | O(n log n) average, O(n²) worst |
| **Space complexity** | O(n) | O(log n) |
| **Stability** | Stable ✅ | Not stable |
| **Adaptiveness** | Not adaptive | Not adaptive |
| **Worst-case input** | None - always same performance | Sorted/reverse sorted |

### Pattern Differences:

**Quick Sort Pattern:**
```cpp
quickSort() {
    partition();  // 💪 Do work FIRST
    quickSort(left);   // Then recurse
    quickSort(right);
}
```

**Merge Sort Pattern:**
```cpp
mergeSort() {
    mergeSort(left);   // Recurse FIRST
    mergeSort(right);  
    merge();          // 💪 Do work AFTER
}
```

## Implementation Variations

### 1. Alternative Copy-Back Method
```cpp
// Method 1: Your approach
for (int i = 0; i < temp.size(); i++) {
    nums[low + i] = temp[i];
}

// Method 2: Index-based approach  
for (int i = low; i <= high; i++) {
    nums[i] = temp[i - low];
}

// Both are mathematically equivalent!
```

### 2. Bottom-Up Merge Sort (Iterative)
```cpp
void bottomUpMergeSort(vector<int>& nums) {
    int n = nums.size();
    
    // Merge subarrays of size 1, 2, 4, 8, 16...
    for (int size = 1; size < n; size *= 2) {
        for (int left = 0; left < n - 1; left += 2 * size) {
            int mid = min(left + size - 1, n - 1);
            int right = min(left + 2 * size - 1, n - 1);
            
            if (mid < right) {
                merge(nums, left, mid, right);
            }
        }
    }
}
```

### 3. Optimized Merge Sort with Insertion Sort
```cpp
void optimizedMergeSort(vector<int>& nums, int low, int high) {
    // Use insertion sort for small subarrays
    if (high - low + 1 <= 10) {
        insertionSort(nums, low, high);
        return;
    }
    
    if (low >= high) return;
    
    int mid = low + (high - low) / 2;
    optimizedMergeSort(nums, low, mid);
    optimizedMergeSort(nums, mid + 1, high);
    
    // Skip merge if already sorted
    if (nums[mid] <= nums[mid + 1]) return;
    
    merge(nums, low, mid, high);
}
```

## Common Mistakes and Debugging Tips

### 1. **Infinite Loop in Merge**
```cpp
// ❌ WRONG - Missing equal case
if (nums[left] < nums[right]) {
    temp.push_back(nums[left]);
    left++;
} else if (nums[left] > nums[right]) {
    temp.push_back(nums[right]);
    right++;
}
// If nums[left] == nums[right], neither pointer advances!

// ✅ CORRECT - Handle equal elements
if (nums[left] <= nums[right]) {
    temp.push_back(nums[left]);
    left++;
} else {
    temp.push_back(nums[right]);
    right++;
}
```

### 2. **Incorrect Array Copy-Back**
```cpp
// ❌ WRONG - Always copies to beginning
for (int i = 0; i < temp.size(); i++) {
    nums[i] = temp[i];  // Overwrites wrong positions!
}

// ✅ CORRECT - Copy to subarray positions
for (int i = 0; i < temp.size(); i++) {
    nums[low + i] = temp[i];  // Copy to correct positions
}
```

### 3. **Off-by-One in Mid Calculation**
```cpp
// ❌ POTENTIAL OVERFLOW
int mid = (low + high) / 2;

// ✅ OVERFLOW SAFE
int mid = low + (high - low) / 2;
```

### 4. **Missing Return Statement**
```cpp
// ❌ WRONG - Missing return
vector<int> mergeSort(vector<int>& nums) {
    mergeSortHelper(nums, 0, nums.size() - 1);
    // Missing return nums;
}
```

## Use Cases and Applications

### When to Use Merge Sort
- **Stability required** - Preserve order of equal elements
- **Guaranteed performance needed** - Always O(n log n)
- **Large datasets** - Consistent performance
- **External sorting** - Can work with data that doesn't fit in memory
- **Linked list sorting** - Natural fit for linked structures
- **Parallel processing** - Easy to parallelize

### When NOT to Use Merge Sort
- **Memory constrained** - Uses O(n) extra space
- **Small arrays** - Overhead not worth it (use insertion sort)
- **In-place sorting required** - Use heap sort or quicksort
- **Cache performance critical** - Quicksort often better

### Real-World Applications
- **Java's Collections.sort()** (for objects)
- **Python's sort()** and **Timsort** (hybrid approach)
- **Database sorting operations**
- **External sorting** for massive datasets
- **Version control systems** (merging file changes)

## Pattern Recognition for LeetCode

Merge Sort concepts appear in many problems:

### 1. **Merge Two Sorted Arrays**
```cpp
// Direct application of merge logic
void merge(vector<int>& nums1, vector<int>& nums2) {
    // Same two-pointer technique as merge sort
}
```

### 2. **Count of Smaller Numbers After Self**
```cpp
// Use merge sort with custom comparison
// Count inversions during merge process
```

### 3. **Sort List (Linked List)**
```cpp
// Merge sort is perfect for linked lists
// No extra space needed for arrays
```

### 4. **Reverse Pairs**
```cpp
// Count pairs where i < j but nums[i] > 2 * nums[j]
// Modify merge sort to count during merge
```

## Algorithm Analysis Summary

### Strengths:
- **Guaranteed O(n log n)** performance
- **Stable** sorting algorithm
- **Predictable** behavior
- **Parallelizable** 
- **Works well** with linked lists

### Weaknesses:
- **O(n) extra space** required
- **Not adaptive** to input patterns
- **More overhead** than quicksort
- **Poor cache performance** due to non-local access

## Key Implementation Insights

### 1. **The Merge Function is the Heart**
- Two-pointer technique for combining sorted arrays
- Handles remaining elements after main comparison loop
- Index mapping: `temp[i] → nums[low + i]`

### 2. **Recursion Does the Splitting**
- Mathematical division: `mid = low + (high - low) / 2`
- Base case: Single elements are already sorted
- Work happens during "return journey" of recursion

### 3. **Bottom-Up vs Top-Down**
- Top-down: Recursive splitting (more intuitive)
- Bottom-up: Iterative merging (better space complexity for call stack)

## Key Takeaways

1. **Master the merge process** - it's the core operation
2. **Understand the recursive tree** - work flows bottom-up
3. **Always use stable comparison** - `<=` not just `<`  
4. **Handle array indexing carefully** - copy to correct positions
5. **Consider space-time tradeoffs** - guaranteed time vs extra space
6. **Recognize merge patterns** - applicable to many problems beyond sorting

**Merge Sort represents the epitome of divide-and-conquer algorithms** - elegant, predictable, and fundamental to understanding recursive problem solving. Its guaranteed performance and stability make it a cornerstone algorithm in computer science, even when other sorts might be faster in practice.

---

**Remember:** Merge sort's strength lies not in being the fastest sort, but in being **reliable, stable, and predictable** - qualities that are invaluable in many real-world applications.
