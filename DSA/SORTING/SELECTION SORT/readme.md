# Selection Sort

## Algorithm Overview

**Core Philosophy:** "Fix position → Find smallest → Place it there"

Selection sort works by repeatedly finding the minimum element from the unsorted portion of the array and placing it at the beginning of the sorted portion.

## Algorithm Steps

1. **Fix position `i`** (starting from 0)
2. **Find smallest element** in the remaining unsorted array (from `i` to `n-1`)
3. **Swap** the smallest element with element at position `i`
4. **Repeat** for next position until entire array is sorted

## Implementation

```cpp
class Solution {
public:
    vector<int> selectionSort(vector<int>& nums) {
        int n = nums.size();
        
        for(int i = 0; i < n-1; i++) {        // Fix position i
            int k = i;                        // Assume current position has minimum
            
            for(int j = i+1; j < n; j++) {    // Scan remaining array
                if(nums[j] < nums[k]) {       // Found smaller element
                    k = j;                    // Update minimum index
                }
            }
            
            swap(nums[i], nums[k]);           // Place minimum at position i
        }
        
        return nums;
    }
};
```

## Visual Trace Example

**Array:** `[64, 25, 12, 22, 11, 90]`

```
Initial: [64, 25, 12, 22, 11, 90]

Iteration 1 (i=0):
- Find min in [64, 25, 12, 22, 11, 90] → 11 (index 4)
- Swap nums[0] with nums[4]
- Result: [11, 25, 12, 22, 64, 90]

Iteration 2 (i=1):
- Find min in [25, 12, 22, 64, 90] → 12 (index 2)
- Swap nums[1] with nums[2]
- Result: [11, 12, 25, 22, 64, 90]

Iteration 3 (i=2):
- Find min in [25, 22, 64, 90] → 22 (index 3)
- Swap nums[2] with nums[3]
- Result: [11, 12, 22, 25, 64, 90]

... and so on
```

## Key Pattern Insights

### Loop Structure
- **Outer loop:** Iterates through positions (0 to n-2)
- **Inner loop:** Finds minimum in remaining unsorted portion
- **Why n-1?** Last element is automatically in correct position after n-1 iterations

### Invariant Maintained
After `k` iterations:
- First `k` positions contain the `k` smallest elements in sorted order
- Remaining positions contain unsorted elements

## Complexity Analysis

### Time Complexity
- **Best Case:** O(n²) - Even on sorted array
- **Average Case:** O(n²) 
- **Worst Case:** O(n²)

**Comparisons:** Always n(n-1)/2 regardless of input
```
Iteration 1: (n-1) comparisons
Iteration 2: (n-2) comparisons
...
Iteration n-1: 1 comparison
Total: 1 + 2 + ... + (n-1) = n(n-1)/2 = O(n²)
```

### Space Complexity
- **O(1)** - In-place sorting algorithm

## Algorithm Properties

### ❌ Non-Adaptive
Selection sort performs the **same number of comparisons** regardless of input:
- Sorted array: O(n²) comparisons
- Reverse sorted: O(n²) comparisons  
- Random array: O(n²) comparisons

**Why?** Algorithm always scans entire remaining array to find minimum, even if minimum is already in the first position.

### ❌ Non-Stable
Selection sort **does NOT preserve** the relative order of equal elements.

**Counter-example:**
```
Input:  [4a, 2, 4b, 1]  (where a,b are identifiers for equal elements)
Output: [1, 2, 4b, 4a]  ❌ 4b comes before 4a now!
```

**Why unstable?** Long-distance swaps can leap-frog over equal elements, changing their relative order.

### ❌ Non-Online
Requires access to the entire array upfront; cannot process streaming data.

## Use Cases

### When to Use Selection Sort
- **Small arrays** (typically n < 20)
- **Memory is extremely constrained** (O(1) space)
- **Simplicity is prioritized** over efficiency
- **Number of swaps needs to be minimized** (exactly n-1 swaps)

### When NOT to Use Selection Sort
- **Large datasets** (O(n²) is too slow)
- **Nearly sorted data** (insertion sort would be better)
- **Stability is required** (use stable sorts like merge sort)
- **Performance is critical** (use O(n log n) algorithms)

## Comparison with Other Basic Sorts

| Property | Selection Sort | Insertion Sort | Bubble Sort |
|----------|----------------|----------------|-------------|
| **Best Time** | O(n²) | O(n) | O(n) |
| **Average Time** | O(n²) | O(n²) | O(n²) |
| **Worst Time** | O(n²) | O(n²) | O(n²) |
| **Space** | O(1) | O(1) | O(1) |
| **Adaptive** | ❌ | ✅ | ✅ |
| **Stable** | ❌ | ✅ | ✅ |
| **Swaps** | O(n) | O(n²) | O(n²) |

## Implementation Notes

### Minor Optimizations
1. **Early termination:** Loop runs `i < n-1` instead of `i < n`
2. **Self-swap check:** Can add `if(i != k)` before swap to avoid unnecessary self-swaps

### Common Mistakes
1. **Starting inner loop from `i` instead of `i+1`**
2. **Swapping inside inner loop instead of after**
3. **Tracking minimum value instead of minimum index**

## Code Variations

### With Swap Count Optimization
```cpp
for(int i = 0; i < n-1; i++) {
    int k = i;
    for(int j = i+1; j < n; j++) {
        if(nums[j] < nums[k]) {
            k = j;
        }
    }
    if(i != k) {  // Avoid unnecessary self-swap
        swap(nums[i], nums[k]);
    }
}
```

### Finding Maximum Instead of Minimum
Selection sort can also work by finding maximum elements and placing them at the end.

---

**Key Takeaway:** Selection sort is simple and uses minimal memory, but its O(n²) time complexity and non-adaptive nature make it suitable only for small datasets or educational purposes.
