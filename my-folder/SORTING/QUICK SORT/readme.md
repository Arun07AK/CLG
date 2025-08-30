# Quick Sort

## Algorithm Overview

**Core Philosophy:** "Divide and Conquer - Split around one element, recursively solve smaller pieces"

Quick Sort is a highly efficient sorting algorithm that uses a divide-and-conquer approach. It works by selecting a 'pivot' element and partitioning the array around it, ensuring all elements smaller than the pivot come before it, and all larger elements come after it.

## Algorithm Steps

1. **Choose a pivot** element from the array
2. **Partition** the array so that:
   - All elements < pivot are on the left
   - All elements ≥ pivot are on the right
   - Pivot is in its final sorted position
3. **Recursively sort** the left and right subarrays
4. **Base case:** Arrays with ≤ 1 element are already sorted

## Core Implementation (Two-Pointer Approach)

```cpp
class Solution {
public:
    vector<int> quickSort(vector<int>& nums) {
        if (nums.empty()) return nums;
        quickSortHelper(nums, 0, nums.size() - 1);
        return nums;
    }
    
private:
    void quickSortHelper(vector<int>& nums, int low, int high) {
        if (low >= high) {  // Base case: 0 or 1 elements
            return;
        }
        
        int pivotIndex = partition(nums, low, high);
        
        // Recursive calls on subarrays
        quickSortHelper(nums, low, pivotIndex - 1);      // Left subarray
        quickSortHelper(nums, pivotIndex + 1, high);    // Right subarray
    }
    
    int partition(vector<int>& nums, int low, int high) {
        int pivot = nums[low];        // Choose first element as pivot
        int left = low + 1;           // Left pointer starts after pivot
        int right = high;             // Right pointer starts at end
        
        while (left <= right) {
            // Find element ≥ pivot from left side (misplaced)
            while (left <= right && nums[left] < pivot) {
                left++;
            }
            
            // Find element < pivot from right side (misplaced)  
            while (left <= right && nums[right] >= pivot) {
                right--;
            }
            
            // Swap misplaced elements if both found
            if (left <= right) {
                swap(nums[left], nums[right]);
                left++;
                right--;
            }
        }
        
        // Place pivot in its correct final position
        swap(nums[low], nums[right]);
        return right;  // Return pivot's final position
    }
};
```

## Visual Trace Example

**Array:** `[3, 6, 1, 8, 2, 5]`

### Initial Partitioning (pivot = 3):
```
Step 1: [3, 6, 1, 8, 2, 5]  pivot=3, left=1, right=5
        Find: nums[1]=6 ≥ 3, nums[5]=5 ≥ 3 → right moves to nums[4]=2 < 3
        Swap: [3, 2, 1, 8, 6, 5]

Step 2: [3, 2, 1, 8, 6, 5]  left=2, right=3  
        Find: nums[2]=1 < 3 → left moves to nums[3]=8 ≥ 3
        Find: nums[3]=8 ≥ 3 → right moves, but right < left
        
Step 3: Pointers crossed, place pivot
        Swap: nums[0] ↔ nums[2] → [1, 2, 3, 8, 6, 5]
                                      ↑
                                 pivot in final position
```

### Recursive Structure:
```
quickSort([1, 2, 3, 8, 6, 5])
├─ Partition around 3: [1, 2, 3, 8, 6, 5]
├─ quickSort([1, 2])     // Left subarray
│  └─ Partition around 1: [1, 2]
│  └─ Base cases
└─ quickSort([8, 6, 5])  // Right subarray  
   └─ Partition around 8: [6, 5, 8]
   └─ quickSort([6, 5]) → [5, 6]
   
Final Result: [1, 2, 3, 5, 6, 8]
```

## Alternative Implementation: Lomuto Partition Scheme

```cpp
class Solution {
public:
    vector<int> quickSortLomuto(vector<int>& nums) {
        quickSortHelper(nums, 0, nums.size() - 1);
        return nums;
    }
    
private:
    void quickSortHelper(vector<int>& nums, int low, int high) {
        if (low < high) {
            int pivotIndex = lomutoPartition(nums, low, high);
            quickSortHelper(nums, low, pivotIndex - 1);
            quickSortHelper(nums, pivotIndex + 1, high);
        }
    }
    
    int lomutoPartition(vector<int>& nums, int low, int high) {
        int pivot = nums[high];  // Choose last element as pivot
        int i = low - 1;         // Index of smaller element
        
        for (int j = low; j < high; j++) {
            if (nums[j] < pivot) {
                i++;
                swap(nums[i], nums[j]);
            }
        }
        
        swap(nums[i + 1], nums[high]);  // Place pivot in correct position
        return i + 1;
    }
};
```

## Complexity Analysis

### Time Complexity

| Case | Complexity | Explanation |
|------|------------|-------------|
| **Best Case** | O(n log n) | Pivot always splits array evenly |
| **Average Case** | O(n log n) | Expected behavior with random data |
| **Worst Case** | O(n²) | Pivot is always min/max (sorted arrays) |

**Detailed Analysis:**
- **Best/Average:** Each level does O(n) work, log n levels → O(n log n)
- **Worst:** Each level does O(n) work, n levels → O(n²)

### Space Complexity
- **Best/Average Case:** O(log n) - Recursion stack depth
- **Worst Case:** O(n) - Unbalanced recursion tree

## Optimization Techniques

### 1. Random Pivot Selection

**Problem:** Deterministic pivot selection leads to O(n²) on sorted data
**Solution:** Choose pivot randomly to guarantee expected O(n log n)

```cpp
int randomizedPartition(vector<int>& nums, int low, int high) {
    // Generate random index between low and high
    int randomIndex = low + rand() % (high - low + 1);
    
    // Swap random element with first element
    swap(nums[low], nums[randomIndex]);
    
    // Proceed with normal partition
    return partition(nums, low, high);
}
```

**Why it works:** 
- Probability of consistently choosing bad pivots becomes negligible
- Expected O(n log n) performance regardless of input pattern
- Industry standard for production quicksort implementations

### 2. Sentinel Values (Advanced Optimization)

**Problem:** Inner loops require boundary checks, slowing performance
**Solution:** Add sentinel values to eliminate bounds checking

```cpp
vector<int> quickSortWithSentinel(vector<int>& nums) {
    if (nums.empty()) return nums;
    
    // Add right sentinel to help left pointer
    nums.push_back(INT_MAX);
    
    quickSortHelper(nums, 0, nums.size() - 2);
    
    // Remove sentinel
    nums.pop_back();
    return nums;
}

int partitionWithSentinel(vector<int>& nums, int low, int high) {
    int pivot = nums[low];
    int left = low + 1;
    int right = high;
    
    while (true) {
        // No boundary check needed - sentinel guarantees stopping
        while (nums[left] < pivot) left++;
        
        // Still need boundary check for right pointer
        while (right > low && nums[right] >= pivot) right--;
        
        if (left >= right) break;
        
        swap(nums[left], nums[right]);
        left++;
        right--;
    }
    
    swap(nums[low], nums[right]);
    return right;
}
```

### 3. Three-Way Partitioning (Dutch National Flag)

**Problem:** Poor performance on arrays with many duplicate elements
**Solution:** Partition into three parts: < pivot, = pivot, > pivot

```cpp
void threeWayQuickSort(vector<int>& nums, int low, int high) {
    if (low >= high) return;
    
    int pivot = nums[low];
    int lt = low;      // nums[low..lt-1] < pivot
    int i = low + 1;   // nums[lt..i-1] == pivot  
    int gt = high;     // nums[gt+1..high] > pivot
    
    while (i <= gt) {
        if (nums[i] < pivot) {
            swap(nums[lt], nums[i]);
            lt++; i++;
        }
        else if (nums[i] > pivot) {
            swap(nums[i], nums[gt]);
            gt--;
            // Don't increment i - need to check swapped element
        }
        else {
            i++;  // nums[i] == pivot
        }
    }
    
    // Recursively sort < and > parts (skip equal elements!)
    threeWayQuickSort(nums, low, lt - 1);
    threeWayQuickSort(nums, gt + 1, high);
}
```

## Algorithm Properties

### ✅ Advantages
- **Fast average performance:** O(n log n) expected time
- **In-place sorting:** O(1) extra space (ignoring recursion stack)
- **Cache-efficient:** Good locality of reference
- **Practical:** Used in many standard libraries

### ❌ Disadvantages  
- **Unstable:** Does not preserve relative order of equal elements
- **Worst-case O(n²):** Poor performance on already sorted data
- **Not adaptive:** Doesn't improve on nearly sorted data
- **Recursion overhead:** Deep recursion on worst-case input

## Comparison with Other Sorting Algorithms

| Algorithm | Best | Average | Worst | Space | Stable | Adaptive |
|-----------|------|---------|--------|-------|---------|----------|
| **Quick Sort** | O(n log n) | O(n log n) | O(n²) | O(log n) | ❌ | ❌ |
| **Merge Sort** | O(n log n) | O(n log n) | O(n log n) | O(n) | ✅ | ❌ |
| **Heap Sort** | O(n log n) | O(n log n) | O(n log n) | O(1) | ❌ | ❌ |
| **Insertion Sort** | O(n) | O(n²) | O(n²) | O(1) | ✅ | ✅ |

## Common Mistakes and Debugging Tips

### 1. **Infinite Loops in Partitioning**
```cpp
// ❌ WRONG - Can cause infinite loop
while (left <= right) {
    while (nums[left] < pivot) left++;
    while (nums[right] >= pivot) right--;
    swap(nums[left], nums[right]);  // Always swaps!
    left++; right--;
}

// ✅ CORRECT - Check before swapping  
while (left <= right) {
    while (left <= right && nums[left] < pivot) left++;
    while (left <= right && nums[right] >= pivot) right--;
    if (left <= right) {  // Check before swap!
        swap(nums[left], nums[right]);
        left++; right--;
    }
}
```

### 2. **Incorrect Pivot Placement**
```cpp
// ❌ WRONG - Should swap with 'right', not 'left'
swap(nums[low], nums[left]);  

// ✅ CORRECT - 'right' points to correct boundary
swap(nums[low], nums[right]);
```

### 3. **Off-by-One Errors in Recursion**
```cpp
// ✅ CORRECT recursive calls
quickSort(nums, low, pivotIndex - 1);      // Exclude pivot
quickSort(nums, pivotIndex + 1, high);    // Exclude pivot
```

### 4. **Missing Boundary Checks**
```cpp
// ❌ DANGEROUS - No bounds checking
while (nums[left] < pivot) left++;  // Could access out of bounds

// ✅ SAFE - Always check bounds
while (left <= right && nums[left] < pivot) left++;
```

## Use Cases and Applications

### When to Use Quick Sort
- **Large datasets** with random/unknown patterns
- **Memory-constrained environments** (in-place sorting)
- **General-purpose sorting** where average performance matters
- **Systems programming** where cache efficiency is important

### When NOT to Use Quick Sort
- **Guaranteed O(n log n) required** (use merge sort or heap sort)
- **Stability is essential** (use merge sort or stable sort)
- **Nearly sorted data** (use insertion sort for small arrays)
- **Adversarial inputs possible** (unless using randomized version)

### Real-World Applications
- **Standard library implementations** (with optimizations)
- **Database sorting algorithms**
- **Graphics and game engines** (for z-buffer sorting)
- **Computational geometry** (sorting points, lines)

## Pattern Recognition for LeetCode

Quick Sort concepts appear in many problems:

### 1. **Kth Largest Element** (QuickSelect)
```cpp
// Use partition to find kth element in O(n) average time
int findKthLargest(vector<int>& nums, int k) {
    return quickSelect(nums, 0, nums.size()-1, nums.size()-k);
}
```

### 2. **Dutch National Flag Problems**
- Sort Colors (3-way partitioning)
- Partition arrays around pivot values

### 3. **Two-Pointer Techniques**
- Problems requiring element rearrangement
- Partitioning based on conditions

## Implementation Variations Summary

### 1. **Standard Two-Pointer (Hoare Partition)**
- **Pros:** Efficient, fewer swaps
- **Cons:** More complex logic
- **Use:** General-purpose implementation

### 2. **Lomuto Partition**
- **Pros:** Simpler logic, easier to understand
- **Cons:** More swaps, slightly slower
- **Use:** Educational purposes, simpler codebase

### 3. **Randomized Quick Sort**
- **Pros:** Guaranteed expected performance
- **Cons:** Non-deterministic behavior
- **Use:** Production systems, unknown input patterns

### 4. **Three-Way Quick Sort**
- **Pros:** Excellent for duplicate-heavy data
- **Cons:** More complex implementation
- **Use:** Data with many duplicate values

## Key Takeaways

1. **Master the partitioning process** - it's the heart of quicksort
2. **Understand the recursive structure** - divide and conquer pattern
3. **Know when to optimize** - random pivot for production code
4. **Debug systematically** - trace pointer movements carefully  
5. **Recognize the pattern** - useful for many partitioning problems
6. **Consider alternatives** - merge sort when stability/guaranteed performance needed

Quick Sort represents a fundamental divide-and-conquer algorithm that balances simplicity, efficiency, and practical utility. While it has worst-case limitations, its average-case performance and in-place nature make it a cornerstone of computer science algorithms.

---

**Remember:** Understanding quicksort deeply builds intuition for many advanced algorithms and problem-solving techniques in competitive programming and software development.
