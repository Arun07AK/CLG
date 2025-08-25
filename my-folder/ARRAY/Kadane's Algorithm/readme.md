# Maximum Subarray (Kadane's Algorithm) - Complete Pattern Guide

## Pattern Classification: Dynamic Programming - Linear Scan Optimization

### Core Problem Template
**Given:** Array of integers (can be positive, negative, or zero)  
**Find:** Contiguous subarray with maximum sum  
**Return:** The maximum sum value  
**Constraint:** Subarray must be non-empty  

## Pattern Recognition Signals

### ✅ **Strong Indicators:**
1. **"Maximum/Minimum sum"** + **"contiguous subarray/substring"**
2. **"Find the best consecutive elements"**
3. **Array with mixed positive/negative numbers**
4. **Need to optimize over all possible ranges**
5. **Linear scan pattern** (can solve in single pass)

### ✅ **Key Phrases to Watch For:**
- "Maximum subarray sum"
- "Largest sum of contiguous elements"  
- "Best consecutive subsequence"
- "Optimal contiguous range"
- "Maximum sum of k consecutive elements" (variant)

### ❌ **When NOT to Use:**
- Need actual subarray elements (not just sum)
- Non-contiguous elements allowed
- Fixed subarray length required
- Multiple subarrays needed
- 2D arrays (different pattern needed)

## The Two Core Implementations

### Implementation 1: Explicit Choice Model (Recommended for Learning)

```cpp
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int best_ending_here = nums[0];    // Best sum ending at current position
        int best_seen_anywhere = nums[0];  // Global maximum found so far
        
        for(int i = 1; i < nums.size(); i++) {
            // DECISION: Extend previous subarray OR start fresh
            best_ending_here = max(nums[i], best_ending_here + nums[i]);
            
            // UPDATE: Track global maximum
            best_seen_anywhere = max(best_seen_anywhere, best_ending_here);
        }
        return best_seen_anywhere;
    }
};
```

**Mental Model:** "At each position, make explicit choice: extend or restart?"

### Implementation 2: Reset on Negative Model (Industry Common)

```cpp
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        long long max_sum = LLONG_MIN;
        long long current_sum = 0;
        
        for(int i = 0; i < nums.size(); i++) {
            current_sum += nums[i];           // Add current element
            
            max_sum = max(max_sum, current_sum);  // Update global max
            
            if(current_sum < 0) {             // Reset if negative
                current_sum = 0;
            }
        }
        return max_sum;
    }
};
```

**Mental Model:** "Keep running sum, reset to 0 when it becomes negative"

## Core Algorithm Insights

### The Fundamental Principle
**When a running sum becomes negative, it's always better to start fresh than to continue**

**Mathematical Proof:**
- If `running_sum < 0` and we encounter `nums[i]`
- Choice A: Continue → `running_sum + nums[i]`  
- Choice B: Start fresh → `nums[i]`
- Since `running_sum < 0`, we have `running_sum + nums[i] < nums[i]`
- Therefore, starting fresh is always better or equal

### The Two-State Dynamic Programming
**State Definition:**
- `dp[i]` = Maximum sum of subarray ending at position i
- **Recurrence:** `dp[i] = max(nums[i], dp[i-1] + nums[i])`
- **Base Case:** `dp[0] = nums[0]`
- **Answer:** `max(dp[0], dp[1], ..., dp[n-1])`

**Space Optimization:** Only need previous state → O(1) space

## Complexity Analysis

| Metric | Complexity | Explanation |
|--------|------------|-------------|
| **Time** | **O(n)** | Single pass through array |
| **Space** | **O(1)** | Only 2 variables needed |
| **Comparisons** | **O(n)** | Constant comparisons per element |
| **Optimal?** | **Yes** | Cannot do better than O(n) |

## Edge Cases & Special Scenarios

### 1. All Negative Numbers
```cpp
Input: [-3, -1, -4, -2]
Output: -1 (least negative number)

Trace (Method 1):
i=1: max(-1, -3+(-1)) = -1, global = -1
i=2: max(-4, -1+(-4)) = -4, global = -1  
i=3: max(-2, -4+(-2)) = -2, global = -1
```

### 2. All Positive Numbers  
```cpp
Input: [1, 2, 3, 4]
Output: 10 (sum of all elements)

Trace: Algorithm will keep extending since all sums are positive
```

### 3. Mixed with Zeros
```cpp
Input: [2, 0, -1, 4]
Output: 5 (subarray [2, 0, -1, 4])

Key: Zero doesn't hurt or help, so algorithm continues through it
```

### 4. Single Element
```cpp
Input: [5] or [-5]
Output: 5 or -5

Base case: Return the single element
```

## Pattern Variations & Extensions

### Variation 1: Return the Actual Subarray
```cpp
vector<int> maxSubArrayElements(vector<int>& nums) {
    int start = 0, end = 0, temp_start = 0;
    int max_sum = INT_MIN, current_sum = 0;
    
    for(int i = 0; i < nums.size(); i++) {
        current_sum += nums[i];
        
        if(current_sum > max_sum) {
            max_sum = current_sum;
            start = temp_start;
            end = i;
        }
        
        if(current_sum < 0) {
            current_sum = 0;
            temp_start = i + 1;
        }
    }
    
    return vector<int>(nums.begin() + start, nums.begin() + end + 1);
}
```

### Variation 2: Maximum Product Subarray
**Different Pattern:** Need to track both max and min (due to negative numbers)
```cpp
int maxProduct(vector<int>& nums) {
    int max_ending_here = nums[0];
    int min_ending_here = nums[0]; 
    int result = nums[0];
    
    for(int i = 1; i < nums.size(); i++) {
        int temp_max = max({nums[i], max_ending_here * nums[i], min_ending_here * nums[i]});
        min_ending_here = min({nums[i], max_ending_here * nums[i], min_ending_here * nums[i]});
        max_ending_here = temp_max;
        result = max(result, max_ending_here);
    }
    return result;
}
```

### Variation 3: Circular Array Maximum Subarray
**Strategy:** Max of (normal Kadane's) and (total_sum - min_subarray)

### Variation 4: Maximum Subarray of Size K
**Different Pattern:** Sliding window technique, not Kadane's

## Related Problems & Pattern Applications

### Direct Applications:
1. **Maximum Subarray Sum** (LeetCode 53) ⭐ Core problem
2. **Maximum Product Subarray** (LeetCode 152)
3. **Maximum Sum Circular Subarray** (LeetCode 918)
4. **Largest Rectangle in Histogram** (uses similar DP principle)

### Similar DP Patterns:
1. **House Robber** - Linear DP with choice
2. **Best Time to Buy/Sell Stock** - Similar optimization pattern
3. **Longest Increasing Subsequence** - DP with choice

### Pattern Recognition Practice:
- **"Maximum/minimum over all ranges"** → Consider Kadane's
- **"Contiguous + optimization"** → Strong signal  
- **"Single pass possible"** → Likely fits this pattern

## Implementation Decision Tree

```
Problem requires maximum contiguous subarray sum?
├─ Yes: Use Kadane's Algorithm
│  ├─ Need just the sum? → Use either implementation
│  ├─ Need actual subarray? → Use tracking variant
│  ├─ Circular array? → Use circular variant  
│  └─ Product instead of sum? → Use product variant
└─ No: Different pattern needed
   ├─ Non-contiguous? → Different DP
   ├─ Fixed size K? → Sliding window
   └─ 2D array? → 2D DP
```

## Common Mistakes & Debugging Tips

### ❌ **Mistake 1:** Processing first element twice
```cpp
// WRONG
int current_sum = nums[0];
for(int i = 0; i < n; i++) { // Should start from i=1
    current_sum = max(nums[i], current_sum + nums[i]);
}
```

### ❌ **Mistake 2:** Using global max for local decisions  
```cpp
// WRONG - using max_sum instead of current_sum
current_sum = max(nums[i], max_sum + nums[i]);
```

### ❌ **Mistake 3:** Not handling all negative arrays
```cpp
// WRONG - initializing max to 0
int max_sum = 0; // Should be INT_MIN or nums[0]
```

### ❌ **Mistake 4:** Integer overflow
```cpp
// POTENTIAL ISSUE - use long long for large ranges
int sum = INT_MAX; // Could overflow on addition
```

### ✅ **Debug Strategy:**
1. **Trace small examples** step by step
2. **Check edge cases:** all negative, all positive, single element
3. **Verify base case:** first element handling
4. **Test overflow:** large numbers

## Advanced Optimizations & Considerations

### Memory Optimization
**Already optimal:** O(1) space, can't improve further

### Cache Performance  
**Excellent:** Sequential access pattern, cache-friendly

### Parallelization
**Difficult:** Inherently sequential due to dependency chain  
**Possible approaches:** Divide & conquer (more complex), parallel prefix sums

### Numerical Stability
**Use `long long`** to prevent integer overflow on large arrays

## Problem-Solving Template

### Step 1: Recognize the Pattern
- Maximum/minimum + contiguous subarray → Kadane's Algorithm

### Step 2: Choose Implementation
```cpp
// Template with error handling
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        if(nums.empty()) return 0; // Edge case
        
        int best_ending_here = nums[0];
        int best_seen_anywhere = nums[0];
        
        for(int i = 1; i < nums.size(); i++) {
            best_ending_here = max(nums[i], best_ending_here + nums[i]);
            best_seen_anywhere = max(best_seen_anywhere, best_ending_here);
        }
        return best_seen_anywhere;
    }
};
```

### Step 3: Test Edge Cases
- Empty array
- Single element (positive/negative)
- All positive
- All negative  
- Mixed with zeros

### Step 4: Optimize if Needed
- Add overflow protection
- Return actual subarray if required
- Handle circular case if needed

## When You've Mastered This Pattern

**You should be able to:**
1. **Instantly recognize** maximum contiguous subarray problems
2. **Choose the right implementation** based on requirements  
3. **Handle all edge cases** without debugging
4. **Extend to variations** (product, circular, etc.)
5. **Explain the intuition** clearly to others

**Next Patterns to Learn:**
- **Sliding Window** (for fixed-size optimization problems)
- **Two Pointers** (for array pair/sum problems)  
- **Prefix Sums** (for range query problems)
- **2D Dynamic Programming** (for grid-based optimization)

## Summary: The Kadane's Algorithm Mindset

**Core Insight:** "Local greedy choices lead to global optimum"

**Decision Framework:** "At each step: extend or restart based on what's better"

**Efficiency Principle:** "Single pass with constant space beats O(n²) brute force"

**Pattern Recognition:** "Maximum contiguous = Kadane's Algorithm"

This pattern is a **fundamental building block** in competitive programming and technical interviews. Master it, and you'll recognize similar optimization opportunities across many other problems!
