# Print Maximum Subarray - Complete Pattern Guide

## Problem Extension: From Sum to Elements

### Base Problem
**Kadane's Algorithm:** Find the **maximum sum** of contiguous subarray

### Extended Problem  
**Enhanced Kadane's:** Find the maximum sum AND **print the actual subarray elements**

### Why This Matters
- **Interviews:** Common follow-up question after solving basic Kadane's
- **Real Applications:** Often need the actual data, not just statistics
- **Pattern Recognition:** Index tracking is crucial in many algorithms

## Core Challenge: Tracking Boundaries

### The Information We Need
1. **Maximum sum found** (same as basic Kadane's)
2. **Where that maximum subarray starts** 
3. **Where that maximum subarray ends**
4. **Current subarray boundaries** (for building process)

### Key Variables Explained

```cpp
long long max_sum = LLONG_MIN;  // Best sum found anywhere
long long current_sum = 0;      // Current running sum
int start = 0;                  // Where CURRENT subarray starts  
int ans_start = -1;             // Where BEST subarray starts
int ans_end = -1;               // Where BEST subarray ends
```

**Critical Insight:** We track **TWO different subarrays simultaneously:**
- **Current subarray:** What we're building right now
- **Best subarray:** The champion we've found so far

## The Complete Algorithm

### Implementation with Index Tracking

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxSubArrayWithPrint(vector<int>& nums) {
        if (nums.empty()) return 0;
        
        long long max_sum = LLONG_MIN;
        long long current_sum = 0;
        int start = 0;
        int ans_start = -1, ans_end = -1;
        
        for (int i = 0; i < nums.size(); i++) {
            // STEP 1: Check if starting fresh
            if (current_sum == 0) {
                start = i;  // New subarray attempt starts here
            }
            
            // STEP 2: Add current element  
            current_sum += nums[i];
            
            // STEP 3: Check if this is new champion
            if (current_sum > max_sum) {
                max_sum = current_sum;
                ans_start = start;  // Champion starts where current starts
                ans_end = i;        // Champion ends at current position
            }
            
            // STEP 4: Reset if negative
            if (current_sum < 0) {
                current_sum = 0;
            }
        }
        
        // Print the actual subarray
        cout << "Maximum subarray: [";
        for (int i = ans_start; i <= ans_end; i++) {
            cout << nums[i];
            if (i < ans_end) cout << ", ";
        }
        cout << "]" << endl;
        
        return max_sum;
    }
};
```

## Step-by-Step Algorithm Logic

### The Four-Step Process

**For each element i:**

1. **Fresh Start Check:** `if (current_sum == 0)` → Mark potential new subarray start
2. **Extend:** Always add `nums[i]` to current sum  
3. **Champion Update:** If current sum is best, save its boundaries
4. **Reset:** If current sum goes negative, reset for next attempt

### Why This Timing Works

**Key Insight:** We check for fresh start **BEFORE** adding the element:

```cpp
if (current_sum == 0) {
    start = i;  // ← This happens BEFORE adding nums[i]
}
current_sum += nums[i];  // ← Element at position i becomes part of new subarray
```

**This ensures:** When `current_sum == 0`, position `i` will be the **first element** of the new subarray.

## Detailed Trace Example

### Array: `[-2, 1, -3, 4, -1, 2, 1, -5, 4]`

**Initial State:**
```
max_sum = -∞, current_sum = 0, start = 0
ans_start = -1, ans_end = -1
```

#### **i=0: nums[0] = -2**
```
1. current_sum == 0? YES → start = 0
2. current_sum = 0 + (-2) = -2
3. current_sum > max_sum? -2 > -∞? YES 
   → max_sum = -2, ans_start = 0, ans_end = 0
4. current_sum < 0? YES → current_sum = 0
```
**State:** Best subarray = `[-2]` with sum -2

#### **i=1: nums[1] = 1**  
```
1. current_sum == 0? YES → start = 1
2. current_sum = 0 + 1 = 1
3. current_sum > max_sum? 1 > -2? YES
   → max_sum = 1, ans_start = 1, ans_end = 1  
4. current_sum < 0? NO
```
**State:** Best subarray = `[1]` with sum 1

#### **i=2: nums[2] = -3**
```
1. current_sum == 0? NO (current_sum = 1)
2. current_sum = 1 + (-3) = -2
3. current_sum > max_sum? -2 > 1? NO
4. current_sum < 0? YES → current_sum = 0
```
**State:** Best subarray = `[1]` with sum 1 (unchanged)

#### **i=3: nums[3] = 4**
```
1. current_sum == 0? YES → start = 3
2. current_sum = 0 + 4 = 4  
3. current_sum > max_sum? 4 > 1? YES
   → max_sum = 4, ans_start = 3, ans_end = 3
4. current_sum < 0? NO
```
**State:** Best subarray = `[4]` with sum 4

#### **i=4: nums[4] = -1**
```
1. current_sum == 0? NO (current_sum = 4)
2. current_sum = 4 + (-1) = 3
3. current_sum > max_sum? 3 > 4? NO  
4. current_sum < 0? NO
```
**State:** Best subarray = `[4]` with sum 4 (unchanged)

#### **i=5: nums[5] = 2**
```
1. current_sum == 0? NO (current_sum = 3)
2. current_sum = 3 + 2 = 5
3. current_sum > max_sum? 5 > 4? YES
   → max_sum = 5, ans_start = 3, ans_end = 5
4. current_sum < 0? NO
```
**State:** Best subarray = `[4, -1, 2]` with sum 5

#### **i=6: nums[6] = 1**
```
1. current_sum == 0? NO (current_sum = 5)
2. current_sum = 5 + 1 = 6
3. current_sum > max_sum? 6 > 5? YES
   → max_sum = 6, ans_start = 3, ans_end = 6  
4. current_sum < 0? NO
```
**State:** Best subarray = `[4, -1, 2, 1]` with sum 6

**Remaining elements don't improve the maximum...**

**Final Result:** `ans_start = 3, ans_end = 6`  
**Subarray:** `[4, -1, 2, 1]` with sum 6

## Key Insights & Patterns

### 1. The Two-Subarray Tracking Pattern

```
Current Subarray:  [Building in progress]
                   ↑
                 start (changes frequently)

Best Subarray:     [Frozen champion]  
                   ↑               ↑
              ans_start         ans_end
              (only updates when new champion found)
```

### 2. The Timing Pattern

**Events in chronological order:**
1. **Detect fresh start** → Update `start`
2. **Build current sum** → Add element
3. **Check if champion** → Update `ans_start, ans_end` if better
4. **Reset if needed** → Prepare for next iteration

### 3. The State Preservation Pattern

**Critical principle:** `ans_start` and `ans_end` **only change** when we find a **genuinely better** subarray.

**Bad attempts don't overwrite good results:**
```cpp
// This protects our champion:
if (current_sum > max_sum) {  // Only update on improvement
    ans_start = start;        // Capture current's start
    ans_end = i;              // Capture current's end  
}
```

## Edge Cases & Special Scenarios

### 1. All Negative Numbers
**Array:** `[-5, -2, -8, -1]`

```
Final state: ans_start = 3, ans_end = 3
Result: [-1] (single least negative element)
```

### 2. All Positive Numbers  
**Array:** `[1, 2, 3, 4]`

```
The algorithm keeps extending:
i=0: [1], i=1: [1,2], i=2: [1,2,3], i=3: [1,2,3,4]
Final: ans_start = 0, ans_end = 3
Result: [1, 2, 3, 4] (entire array)
```

### 3. Single Element
**Array:** `[42]` or `[-42]`

```
i=0: start=0, sum=42, ans_start=0, ans_end=0  
Result: [42] or [-42]
```

### 4. Multiple Optimal Subarrays
**Array:** `[3, -3, 3]`

```
Both [3] at start and [3] at end have sum=3
Algorithm returns: First occurrence (ans_start=0, ans_end=0)
Result: [3] (first one)
```

## Alternative Implementations

### Approach 1: Using Explicit Choice Logic

```cpp
vector<int> maxSubArrayExplicit(vector<int>& nums) {
    int current_sum = nums[0];
    int max_sum = nums[0];
    int start = 0, ans_start = 0, ans_end = 0;
    
    for (int i = 1; i < nums.size(); i++) {
        // Explicit choice: extend or restart
        if (nums[i] > current_sum + nums[i]) {
            current_sum = nums[i];  // Start fresh
            start = i;
        } else {
            current_sum = current_sum + nums[i];  // Extend
        }
        
        if (current_sum > max_sum) {
            max_sum = current_sum;
            ans_start = start;
            ans_end = i;
        }
    }
    
    return vector<int>(nums.begin() + ans_start, nums.begin() + ans_end + 1);
}
```

### Approach 2: Return Multiple Results

```cpp
struct SubarrayResult {
    vector<int> elements;
    int sum;
    int start_index;
    int end_index;
};

SubarrayResult maxSubArrayComplete(vector<int>& nums) {
    // Implementation that returns all information
    long long max_sum = LLONG_MIN;
    long long current_sum = 0;
    int start = 0, ans_start = -1, ans_end = -1;
    
    for (int i = 0; i < nums.size(); i++) {
        if (current_sum == 0) start = i;
        current_sum += nums[i];
        
        if (current_sum > max_sum) {
            max_sum = current_sum;
            ans_start = start;
            ans_end = i;
        }
        
        if (current_sum < 0) current_sum = 0;
    }
    
    vector<int> result_elements(nums.begin() + ans_start, nums.begin() + ans_end + 1);
    return {result_elements, max_sum, ans_start, ans_end};
}
```

## Common Mistakes & Debugging

### ❌ Mistake 1: Updating ans_start at wrong time
```cpp
// WRONG - updates ans_start every fresh start
if (current_sum == 0) {
    start = i;
    ans_start = i;  // ← BUG! Overwrites champion location
}
```

**Problem:** Loses track of where actual best subarray was found.

### ❌ Mistake 2: Wrong boundary calculation  
```cpp
// WRONG - off-by-one error in printing
for (int i = ans_start; i < ans_end; i++) {  // Should be i <= ans_end
    cout << nums[i];
}
```

### ❌ Mistake 3: Not handling empty arrays
```cpp
// Add this check at beginning:
if (nums.empty()) {
    cout << "Empty array" << endl;
    return 0;
}
```

### ❌ Mistake 4: Integer overflow  
```cpp
// Use long long for large arrays:
long long max_sum = LLONG_MIN;  // Not INT_MIN
long long current_sum = 0;      // Not int
```

### ✅ Debug Strategy
1. **Add print statements** after each step to trace variables
2. **Test with small arrays** first (3-4 elements)
3. **Check edge cases:** all negative, all positive, single element
4. **Verify boundaries:** `ans_start <= ans_end` always
5. **Manual trace:** Compare with hand-calculated result

## Testing Framework

### Comprehensive Test Suite

```cpp
void runTests() {
    vector<vector<int>> test_cases = {
        {-2, 1, -3, 4, -1, 2, 1, -5, 4},  // Classic case
        {-2, -3, -1, -5},                  // All negative  
        {1, 2, 3, 4},                      // All positive
        {5},                               // Single positive
        {-5},                              // Single negative
        {1, -2, 1},                        // Multiple segments
        {0, 0, 0},                         // All zeros
    };
    
    Solution sol;
    for (int i = 0; i < test_cases.size(); i++) {
        cout << "Test " << i + 1 << ": ";
        int result = sol.maxSubArrayWithPrint(test_cases[i]);
        cout << "Sum: " << result << endl << endl;
    }
}
```

### Expected Outputs
```
Test 1: Maximum subarray: [4, -1, 2, 1], Sum: 6
Test 2: Maximum subarray: [-1], Sum: -1  
Test 3: Maximum subarray: [1, 2, 3, 4], Sum: 10
Test 4: Maximum subarray: [5], Sum: 5
Test 5: Maximum subarray: [-5], Sum: -5
Test 6: Maximum subarray: [1], Sum: 1 (first or last [1])
Test 7: Maximum subarray: [0], Sum: 0 (any single 0)
```

## Complexity Analysis

| Metric | Complexity | Notes |
|--------|------------|--------|
| **Time** | **O(n)** | Single pass through array |
| **Space** | **O(1)** | Only tracking variables (excluding output) |
| **Output Space** | **O(k)** | Where k = length of result subarray |

## Real-World Applications

### Use Cases Where You Need Actual Elements
1. **Stock Trading:** Need actual time periods, not just profit
2. **Data Analysis:** Need actual data points causing peak performance  
3. **Signal Processing:** Need actual signal segments with maximum energy
4. **Game Development:** Need actual move sequences with highest score
5. **Bioinformatics:** Need actual DNA subsequences with highest score

### Production Considerations
- **Memory Management:** For very large arrays, consider streaming approach
- **Thread Safety:** Algorithm is read-only on input, inherently thread-safe  
- **Error Handling:** Add bounds checking and null pointer guards
- **Performance:** Already optimal for single-threaded execution

## Pattern Recognition for Interviews

### When Interviewer Asks This Follow-up
**After solving basic Kadane's, they often ask:** *"Can you also return/print the actual subarray?"*

**Your Response Strategy:**
1. **Acknowledge:** "Great follow-up! I need to track indices."
2. **Explain:** "I'll need variables to track current and best boundaries."  
3. **Implement:** Show the enhanced version with proper timing
4. **Test:** Walk through a small example to verify correctness

### What This Demonstrates to Interviewer
- **Extension Thinking:** Can build on basic algorithms
- **Index Management:** Comfortable with boundary tracking  
- **Code Organization:** Can add features without breaking existing logic
- **Edge Case Awareness:** Considers boundary conditions

## Summary: The Index Tracking Pattern

### Core Principle
**Separate tracking of current process vs best result found**

### Key Variables Pattern
```cpp
// Process tracking (changes frequently)  
int current_state;
int current_boundaries;

// Result tracking (changes only on improvement)
int best_result;  
int best_boundaries;
```

### Update Timing Pattern  
```cpp
// 1. Update current process state
// 2. Check if current is better than best
// 3. If better: update best result AND best boundaries
// 4. Continue/reset current process as needed
```

### Critical Success Factor
**Never update result boundaries until you're sure you've found something better!**

This pattern appears in many algorithms where you need to track the **location** of optimal results, not just the optimal **values**.
