# Dutch National Flag Pattern - Complete Guide & Implementation

## Core Pattern: 3-Way Partitioning with Invariants

### Problem Template
**Given:** Array with elements that can be classified into exactly **3 categories**
**Goal:** Partition array so all elements of category A come first, then B, then C
**Constraint:** In-place (O(1) extra space), single pass (O(n) time)

### Classic Implementation

```cpp
class Solution {
public:
    void sortZeroOneTwo(vector<int>& nums) {
        int n = nums.size();
        int low = 0;   // Boundary for 0s
        int mid = 0;   // Current element being processed
        int high = n-1; // Boundary for 2s
        
        while(mid <= high) {
            if(nums[mid] < 1) {        // Found a 0
                swap(nums[low], nums[mid]);
                low++;
                mid++;  // Safe to advance - we know what we swapped
            }
            else if(nums[mid] > 1) {   // Found a 2
                swap(nums[high], nums[mid]);
                high--;
                // NO mid++! Must examine unknown element from high
            }
            else {                     // Found a 1
                mid++;  // Already in correct position
            }
        }
    }
};
```

## The Sacred Invariants

**Mental Model:** Array is divided into 4 zones at all times:

```
[Zone1: 0s] [Zone2: 1s] [Zone3: Unknown] [Zone4: 2s]
     ↑           ↑           ↑              ↑
   0...low-1  low...mid-1  mid...high   high+1...n-1
```

**Invariant Promises:**
1. **`[0...low-1]`**: Contains ONLY 0s ✅
2. **`[low...mid-1]`**: Contains ONLY 1s ✅
3. **`[mid...high]`**: Contains UNKNOWN elements ❓
4. **`[high+1...n-1]`**: Contains ONLY 2s ✅

**Termination:** When `mid > high`, the unknown zone disappears = array is sorted!

## Decision Logic Deep Dive

### Case 1: `nums[mid] = 0` (Element belongs in Zone 1)
```cpp
swap(nums[low], nums[mid]);
low++;    // Expand Zone 1
mid++;    // Safe because nums[low] was from processed Zone 2 (must be 1)
```

**Why `mid++` is safe:** 
- If `low == mid`: We're swapping with ourselves
- If `low < mid`: `nums[low]` is from the processed 1s zone (invariant guarantees it's a 1)

### Case 2: `nums[mid] = 2` (Element belongs in Zone 4)
```cpp
swap(nums[high], nums[mid]);
high--;   // Expand Zone 4 leftward  
// NO mid++! nums[high] was UNKNOWN - must examine it
```

**Why NO `mid++`:** The element from `high` position is unprocessed and could be 0, 1, or 2.

### Case 3: `nums[mid] = 1` (Element belongs in Zone 2)
```cpp
mid++;    // Expand Zone 2, shrink unknown zone
```

**Why this works:** Element is already correctly positioned relative to current zones.

## Critical Bug Analysis

### ❌ **The Fatal Mistake:**
```cpp
// WRONG CODE:
else if(nums[mid] > 1) {
    swap(nums[high], nums[mid]);
    high--;
    mid++;  // ← BUG! Skips unknown element
}
```

### **Concrete Failing Example:** `[1, 2, 0]`

**Buggy Trace:**
```
Initial: [1, 2, 0]  low=0, mid=0, high=2

Step 1: nums[0]=1 → mid=1
Step 2: nums[1]=2 → swap with nums[2]=0 → [1, 0, 2]
        high=1, mid=2 (BUG!)
Step 3: mid > high → STOP

Result: [1, 0, 2] ❌ (0 is in wrong position!)
```

**Correct Trace:**
```
Initial: [1, 2, 0]  low=0, mid=0, high=2

Step 1: nums[0]=1 → mid=1  
Step 2: nums[1]=2 → swap with nums[2]=0 → [1, 0, 2]
        high=1, mid stays 1
Step 3: nums[1]=0 → swap with nums[0]=1 → [0, 1, 2]
        low=1, mid=2
Step 4: mid > high → STOP

Result: [0, 1, 2] ✅
```

## Complexity Analysis

**Time Complexity:** O(n)
- Each element is examined at most once
- Each element is swapped at most once
- Single pass through the array

**Space Complexity:** O(1)
- In-place algorithm
- Only uses constant extra space for pointers

## Pattern Recognition Signals

**When to use Dutch National Flag pattern:**

### ✅ **Strong Signals:**
1. **Exactly 3 distinct values** or 3 categories
2. **In-place sorting** requirement
3. **Linear time** needed/preferred
4. Problem mentions "partition" or "segregate"
5. Values have natural ordering (0 < 1 < 2)

### ✅ **Problem Variations:**
- Sort array of 0s, 1s, and 2s
- Partition array: negatives, zeros, positives
- Sort RGB colors
- Move all specific values to ends
- Partition around a pivot (QuickSort)

### ❌ **When NOT to use:**
- More than 3 categories (need different approach)
- Elements don't have clear classification
- Stability required (this is unstable)
- Need to maintain relative order within categories

## Extensions and Variations

### **2-Way Partitioning** (Dutch Flag Simplified)
```cpp
// Partition 0s and 1s
int left = 0, right = n-1;
while(left < right) {
    if(nums[left] == 0) left++;
    else if(nums[right] == 1) right--;  
    else swap(nums[left++], nums[right--]);
}
```

### **k-Way Partitioning** (General Case)
For k > 3 categories, typically need:
- Counting sort approach: O(n + k) time, O(k) space
- Multiple passes: O(k*n) time, O(1) space
- Custom data structures for complex cases

### **QuickSort Partition** (3-way)
```cpp
// Partition around pivot with equal elements handling
int partition3Way(vector<int>& arr, int pivot) {
    int low = 0, mid = 0, high = arr.size() - 1;
    
    while(mid <= high) {
        if(arr[mid] < pivot) {
            swap(arr[low++], arr[mid++]);
        }
        else if(arr[mid] > pivot) {
            swap(arr[mid], arr[high--]);
        }
        else {
            mid++; // arr[mid] == pivot
        }
    }
    return low; // Return boundary of pivot section
}
```

## Common Pitfalls & Debug Tips

### ❌ **Mistake 1:** Wrong loop condition
```cpp
while(mid < high)  // Wrong! Should be mid <= high
```
**Problem:** Misses last element when mid == high

### ❌ **Mistake 2:** Incrementing mid after high swap
```cpp
if(nums[mid] > 1) {
    swap(nums[high], nums[mid]);
    high--;
    mid++;  // BUG!
}
```
**Problem:** Skips processing unknown element from high position

### ❌ **Mistake 3:** Wrong pointer initialization
```cpp
int mid = n/2;  // Wrong! Should be mid = 0
```
**Problem:** Misses elements at the beginning

### ✅ **Debug Strategy:**
1. **Check invariants** after each step
2. **Trace small examples** step by step  
3. **Verify zone boundaries** are maintained
4. **Test edge cases:** all same elements, already sorted, reverse sorted

## Real-World Applications

### **System Design Applications:**
1. **Load Balancing:** Partition requests by priority (low, medium, high)
2. **Database Indexing:** Partition records by status (active, pending, archived)
3. **Network Routing:** Route packets by priority class
4. **Memory Management:** Segregate memory blocks by size category

### **Algorithm Applications:**
1. **QuickSort optimization:** 3-way partitioning for arrays with many duplicates
2. **Selection algorithms:** Efficient pivot-based selection
3. **Data preprocessing:** Clean and organize data categories
4. **Computer Graphics:** Sort objects by depth/transparency

## Mental Models for Mastery

### **The Shrinking Unknown Zone**
- Start: Entire array is unknown
- Progress: Unknown zone shrinks from both ends  
- End: Unknown zone disappears, array is partitioned

### **The Conveyor Belt**
- `mid` is the "inspection point"
- Elements flow left (0s), stay (1s), or flow right (2s)
- Never skip inspection of incoming elements

### **The Three Buckets**
- Imagine three physical buckets: left (0s), middle (1s), right (2s)
- Each element gets examined once and thrown into correct bucket
- Buckets grow until all elements are classified

## Practice Problems

**Beginner:**
- Sort 0s and 1s (2-way partition)
- Move all zeros to end
- Partition array into even/odd

**Intermediate:**  
- Sort 0s, 1s, 2s (classic Dutch flag)
- Partition negative, zero, positive
- QuickSort with 3-way partitioning

**Advanced:**
- Sort array by absolute values with 3 categories
- Partition linked list around value
- K-way partitioning problems

## Key Takeaways

1. **Master the invariants** - they guarantee correctness
2. **Understand processed vs unprocessed** - critical for pointer movement
3. **Single pass efficiency** - each element examined exactly once
4. **In-place transformation** - uses array as workspace
5. **Pattern generalizes** - applies to any 3-way classification problem

**Remember:** This isn't just about sorting 0s, 1s, 2s - it's a fundamental **partitioning pattern** that appears throughout computer science!
