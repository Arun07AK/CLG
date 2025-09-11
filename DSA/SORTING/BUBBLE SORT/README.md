# Bubble Sort - Complete Implementation & Pattern Analysis

## Core Algorithm

```cpp
class Solution {
public:
    vector<int> bubbleSort(vector<int>& nums) {
        int n = nums.size();
        int flag = 0;
        
        for(int i = 0; i < n-1; i++) {
            flag = 0;  // CRITICAL: Reset flag for each pass
            
            for(int j = 0; j < n-i-1; j++) {
                if(nums[j] > nums[j+1]) {
                    swap(nums[j], nums[j+1]);
                    flag = 1;  // Mark that a swap occurred
                }
            }
            
            if(flag == 0) {  // No swaps in this pass = sorted
                break;
            }
        }
        return nums;
    }
};
```

## Key Patterns & Insights

### 1. **Adaptive Algorithm Pattern**
- **Definition**: Algorithm that performs better on inputs that are "close to" the best case
- **Implementation**: Early termination when no swaps occur in a complete pass
- **Why it works**: If no swaps happen, array is guaranteed to be sorted

### 2. **Flag Reset Pattern**
```cpp
for(each iteration) {
    reset_detection_variable = initial_state;  // Fresh start
    // Process current iteration
    if(detection_variable == target_condition) {
        break;  // Condition met
    }
}
```

**Critical Rule**: Detection variables must be reset per iteration to detect current iteration's behavior, not cumulative behavior.

### 3. **Correctness vs Optimization Separation**

| Aspect | With Flag Reset | Without Flag Reset |
|--------|----------------|-------------------|
| **Correctness** | ✅ Sorts correctly | ✅ Sorts correctly |
| **Best Case** | O(n) | O(n²) |
| **Worst Case** | O(n²) | O(n²) |
| **Adaptive** | ✅ Yes | ❌ No |

**Key Insight**: Optimizations can be independent of core algorithmic logic.

## Time Complexity Analysis

### Best Case: O(n)
- **When**: Array is already sorted
- **Why**: First pass detects no swaps, algorithm terminates
- **Example**: [1, 2, 3, 4, 5]

### Average Case: O(n²)
- **When**: Random order elements
- **Why**: Expected number of inversions requires multiple passes

### Worst Case: O(n²)
- **When**: Array is reverse sorted
- **Why**: Maximum number of swaps needed
- **Example**: [5, 4, 3, 2, 1]

## Space Complexity: O(1)
- In-place sorting algorithm
- Only uses constant extra space for variables

## When to Use Bubble Sort

### ✅ **Good For:**
1. **Educational purposes** - Easy to understand and implement
2. **Small datasets** - Simple and sufficient for small n
3. **Nearly sorted data** - Adaptive behavior shines here
4. **Stable sorting needed** - Bubble sort is stable
5. **Memory constrained** - O(1) space complexity

### ❌ **Avoid For:**
1. **Large datasets** - O(n²) becomes prohibitive
2. **Random data** - Other algorithms much faster
3. **Performance critical** - Use quicksort, mergesort, or heapsort

## Pattern Recognition Signals

**When you see these clues, think bubble sort:**
- Small input size mentioned
- "Stable sort" requirement
- "In-place" constraint
- Educational/interview context
- Nearly sorted input mentioned

## Implementation Variants

### 1. **Basic Bubble Sort** (No optimization)
```cpp
for(int i = 0; i < n-1; i++) {
    for(int j = 0; j < n-i-1; j++) {
        if(nums[j] > nums[j+1]) {
            swap(nums[j], nums[j+1]);
        }
    }
}
```

### 2. **Optimized Bubble Sort** (Early termination)
```cpp
// The version we implemented above
```

### 3. **Cocktail Shaker Sort** (Bidirectional bubble sort)
```cpp
// Alternate direction each pass - can be faster on some inputs
```

## Common Mistakes & Debug Tips

### ❌ **Mistake 1**: Forgetting flag reset
```cpp
int flag = 0;  // Only set once
for(int i = 0; i < n-1; i++) {
    // Missing: flag = 0;
    // Rest of code...
}
```
**Result**: Optimization doesn't work after first pass with swaps.

### ❌ **Mistake 2**: Wrong loop bounds
```cpp
for(int j = 0; j < n; j++)  // Should be n-i-1
```
**Result**: Array out of bounds access.

### ❌ **Mistake 3**: Wrong flag logic
```cpp
if(flag == 1) break;  // Should be flag == 0
```
**Result**: Breaks immediately if any swap occurs.

## Algorithm Properties Summary

| Property | Value |
|----------|-------|
| **Stable** | ✅ Yes |
| **In-place** | ✅ Yes |
| **Adaptive** | ✅ Yes (with optimization) |
| **Online** | ❌ No |
| **Comparison-based** | ✅ Yes |

## Pattern Connections

This **adaptive early termination** pattern appears in:
- **Insertion Sort** - Can stop when element finds its position
- **Selection Sort** - Less applicable (always scans remaining)
- **Iterative algorithms** - Detecting convergence
- **Graph algorithms** - Detecting no more changes in relaxation

## Mental Model
Think of bubble sort as **repeatedly floating the largest unsorted element to its correct position**, like bubbles rising to the surface. Each pass guarantees one more element is in its final position.
