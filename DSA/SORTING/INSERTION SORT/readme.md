# Insertion Sort

## Algorithm Overview

**Core Philosophy:** "Take the next element and put it in the right place among what's already sorted"

Insertion sort builds the final sorted array one element at a time. It takes each element from the unsorted portion and inserts it into its correct position within the already-sorted portion.

## Algorithm Steps

1. **Start from the second element** (index 1) - first element is trivially sorted
2. **Take current element** (key) from unsorted portion
3. **Compare with sorted elements** moving backwards
4. **Shift larger elements right** to make space
5. **Insert key** in the correct position
6. **Repeat** until all elements are processed

## Implementation

```cpp
class Solution {
public:
    vector<int> insertionSort(vector<int>& nums) {
        int n = nums.size();
        
        for(int i = 1; i < n; i++) {          // Start from second element
            int key = nums[i];                // Element to be inserted
            int j = i - 1;                    // Last element of sorted portion
            
            // Shift elements greater than key to the right
            while(j >= 0 && nums[j] > key) {
                nums[j + 1] = nums[j];        // Shift right
                j--;                          // Move left
            }
            
            nums[j + 1] = key;                // Insert key at correct position
        }
        
        return nums;
    }
};
```

## Key Pattern Insights

### Why `j + 1` for Insertion?
When the while loop exits, `j` points to:
- **Case 1:** `j = -1` (all elements were shifted) → Insert at position 0 = `j + 1`
- **Case 2:** Element that should stay LEFT of key → Insert at `j + 1`

**Mental Model:** `j` points to the "last element that earned the right to stay left of our key"

### Shift-and-Insert vs Swap Pattern
- **Efficient Approach:** Shift multiple elements, insert once
- **Inefficient Approach:** Swap adjacent elements repeatedly (bubble-like)

## Visual Trace Example

**Array:** `[5, 2, 4, 6, 1, 3]`

```
Initial: [5, 2, 4, 6, 1, 3]
         ↑
      sorted

Iteration 1 (i=1, key=2):
- Compare 2 with 5: 2 < 5, shift 5 right
- Array: [5, 5, 4, 6, 1, 3], j=-1
- Insert 2 at position 0: [2, 5, 4, 6, 1, 3]

Iteration 2 (i=2, key=4):
- Compare 4 with 5: 4 < 5, shift 5 right
- Array: [2, 5, 5, 6, 1, 3]
- Compare 4 with 2: 4 > 2, stop
- Insert 4 at position 2: [2, 4, 5, 6, 1, 3]

Iteration 3 (i=3, key=6):
- Compare 6 with 5: 6 > 5, no shift needed
- Insert 6 at position 3: [2, 4, 5, 6, 1, 3]

... and so on
```

## Complexity Analysis

### Time Complexity
- **Best Case:** O(n) - Already sorted array
- **Average Case:** O(n²) - Random permutation
- **Worst Case:** O(n²) - Reverse sorted array

**Detailed Analysis:**
```
Best Case (sorted): [1, 2, 3, 4, 5]
- Each element needs only 1 comparison
- Total: n-1 comparisons = O(n)

Worst Case (reverse): [5, 4, 3, 2, 1]  
- Element at position i needs i comparisons
- Total: 1 + 2 + 3 + ... + (n-1) = n(n-1)/2 = O(n²)
```

### Space Complexity
- **O(1)** - In-place sorting algorithm

## Algorithm Properties

### ✅ Adaptive
Insertion sort **adapts** to input characteristics:
- **Nearly sorted:** O(n) time complexity
- **Few inversions:** Performs much better than O(n²)
- **Completely sorted:** Only n-1 comparisons needed

**Why adaptive?** The inner while loop terminates early when elements are already in order.

### ✅ Stable
Insertion sort **preserves** the relative order of equal elements.

**Example:**
```
Input:  [4a, 2, 4b, 1]
Output: [1, 2, 4a, 4b]  ✅ 4a still comes before 4b
```

**Why stable?** We only shift elements that are **strictly greater** than the key, never equal elements.

### ✅ Online
Can process elements as they arrive - doesn't need the entire array upfront.

### ✅ In-Place
Sorts the array using only O(1) extra memory.

## Use Cases

### When to Use Insertion Sort
- **Small arrays** (typically n < 50)
- **Nearly sorted data** (takes advantage of O(n) best case)
- **Online algorithms** (elements arrive one at a time)
- **Stability is required**
- **Simple implementation needed**
- **Hybrid algorithms** (used in quicksort/mergesort for small subarrays)

### When NOT to Use Insertion Sort
- **Large datasets** (O(n²) worst case is too slow)
- **Random data** (no advantage over other O(n²) sorts)
- **Performance-critical applications** (use O(n log n) algorithms)

## Comparison with Other Basic Sorts

| Property | Insertion Sort | Selection Sort | Bubble Sort |
|----------|----------------|----------------|-------------|
| **Best Time** | O(n) | O(n²) | O(n) |
| **Average Time** | O(n²) | O(n²) | O(n²) |
| **Worst Time** | O(n²) | O(n²) | O(n²) |
| **Space** | O(1) | O(1) | O(1) |
| **Adaptive** | ✅ | ❌ | ✅ |
| **Stable** | ✅ | ❌ | ✅ |
| **Online** | ✅ | ❌ | ❌ |
| **Swaps** | O(n²) | O(n) | O(n²) |

### Insertion vs Selection Sort - Key Differences

| Aspect | Insertion Sort | Selection Sort |
|--------|----------------|----------------|
| **Philosophy** | Place element correctly | Find minimum, place it |
| **Sorted Portion** | Contains processed elements | Contains globally smallest elements |
| **Performance on Nearly Sorted** | O(n) - Excellent | O(n²) - No improvement |
| **Number of Swaps** | Variable (0 to n²) | Fixed (exactly n-1) |
| **Stability** | Stable | Not stable |

## Implementation Notes

### Common Mistakes
1. **Using `nums[j] = key` instead of `nums[j + 1] = key`**
2. **Starting loop from index 0 instead of 1**
3. **Forgetting boundary check `j >= 0`**
4. **Using inefficient swapping instead of shifting**

### Optimization Techniques
1. **Binary search insertion** - Find position using binary search (O(n log n) comparisons)
2. **Early termination** - Stop if no shifts needed in an iteration
3. **Sentinel values** - Add sentinel to avoid boundary checks

## Code Variations

### Binary Insertion Sort
```cpp
// Find insertion position using binary search
int binarySearch(vector<int>& nums, int key, int low, int high) {
    while(low <= high) {
        int mid = low + (high - low) / 2;
        if(nums[mid] > key) high = mid - 1;
        else low = mid + 1;
    }
    return low;
}

vector<int> binaryInsertionSort(vector<int>& nums) {
    for(int i = 1; i < nums.size(); i++) {
        int key = nums[i];
        int pos = binarySearch(nums, key, 0, i - 1);
        
        // Shift elements
        for(int j = i; j > pos; j--) {
            nums[j] = nums[j - 1];
        }
        nums[pos] = key;
    }
    return nums;
}
```

### Recursive Insertion Sort
```cpp
void insertionSortRecursive(vector<int>& nums, int n) {
    if(n <= 1) return;
    
    insertionSortRecursive(nums, n - 1);  // Sort first n-1 elements
    
    // Insert last element at correct position
    int key = nums[n - 1];
    int j = n - 2;
    while(j >= 0 && nums[j] > key) {
        nums[j + 1] = nums[j];
        j--;
    }
    nums[j + 1] = key;
}
```

## Practical Applications

### Hybrid Sorting Algorithms
Many advanced sorting algorithms use insertion sort for small subarrays:
- **Timsort** (Python's default sort)
- **Introsort** (C++ std::sort)
- **Quicksort optimizations**

**Why?** Insertion sort has low overhead and performs well on small arrays despite O(n²) complexity.

### Real-world Scenarios
- **Sorting playing cards** - Natural human sorting method
- **Maintaining sorted lists** with insertions
- **Online data processing** - sort as data arrives

---

**Key Takeaway:** Insertion sort is simple, stable, and adaptive. Its O(n) best-case performance on nearly sorted data makes it valuable for small arrays and as a subroutine in hybrid algorithms, despite its O(n²) worst-case complexity.
