# **DSA Pattern: 3Sum (Sort + Fix One + Two Pointers)**

## **🎯 Pattern Recognition Triggers**

### **When to Use This Pattern:**
```
✅ TRIGGER PHRASES:
- "Find THREE elements that sum to target/zero"
- "Return all triplets that sum to X"
- "Three numbers with given sum"
- "Triplets that satisfy condition"
- "No duplicate triplets allowed"
- "All unique combinations of three elements"

✅ PROBLEM STRUCTURE:
- Need exactly 3 elements from array
- Sum condition: a + b + c = target (often target = 0)
- Return all valid combinations (not just count)
- Duplicate triplets forbidden in result
- Order of triplets doesn't matter
- Can use same element in multiple triplets (different indices)
```

## **🔍 Pattern Recognition Checklist**
```
□ Need to find exactly THREE elements?
□ Elements must satisfy sum condition?
□ Return all valid combinations (not just first)?
□ Duplicate combinations should be avoided?
□ Array can be modified (sorting allowed)?
□ Brute force O(n³) too slow for constraints?

If ✅ → Use Sort + Fix One + Two Pointers Pattern!
```

## **📝 Core Mathematical Insights**

### **Key Strategy - Problem Reduction:**
```
3Sum Problem → Fix one element + 2Sum Problem
a + b + c = 0 → Fix a, find b + c = -a

Transform: "Find 3 elements" → "For each element, find 2 elements"
Result: O(n³) brute force → O(n²) optimized solution
```

### **Duplicate Prevention Strategy:**
```
Three levels of duplicate handling required:
1. Fixed element (i): Skip same values in outer loop
2. Left pointer: Skip same values after moving left
3. Right pointer: Skip same values after moving right

All three must be handled to prevent duplicate triplets
```

## **🚨 Critical Implementation Details**

### **Sort Requirement:**
```cpp
// MUST sort array first for two pointers to work
sort(nums.begin(), nums.end());
// Two pointers technique only works on sorted data
```

### **Triple Duplicate Handling:**
```cpp
// Level 1: Skip duplicate fixed elements
if(i > 0 && nums[i] == nums[i-1]) continue;

// Level 2: Skip duplicate left values  
while(left < right && nums[left] == nums[left-1]) left++;

// Level 3: Skip duplicate right values
while(left < right && nums[right] == nums[right+1]) right--;
```

### **Boundary Conditions:**
```cpp
// Two pointers boundaries
left = i + 1;  // Start after fixed element
right = n - 1; // Start at end
while(left < right)  // Ensure different elements (no same index twice)
```

## **📝 Optimized Implementation Template**

```cpp
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> result;
        
        // Step 1: Sort array for two pointers technique
        sort(nums.begin(), nums.end());
        
        // Step 2: Fix each element as first element of triplet
        for(int i = 0; i < n - 2; i++) {  // n-2 to leave room for j,k
            // Skip duplicate fixed elements
            if(i > 0 && nums[i] == nums[i-1]) continue;
            
            // Step 3: Two pointers for remaining elements
            int left = i + 1;
            int right = n - 1;
            int target = -nums[i];  // We want nums[left] + nums[right] = target
            
            while(left < right) {
                int sum = nums[left] + nums[right];
                
                if(sum == target) {
                    // Found valid triplet
                    result.push_back({nums[i], nums[left], nums[right]});
                    
                    // Move both pointers
                    left++;
                    right--;
                    
                    // Skip duplicates for both pointers
                    while(left < right && nums[left] == nums[left-1]) left++;
                    while(left < right && nums[right] == nums[right+1]) right--;
                }
                else if(sum < target) {
                    left++;   // Need larger sum
                }
                else {
                    right--;  // Need smaller sum
                }
            }
        }
        
        return result;
    }
};
```

## **⚡ Key Optimization Techniques**

### **1. Early Termination Optimizations:**
```cpp
// Skip if remaining elements can't form valid triplet
if(nums[i] > 0) break;  // If sorted array starts positive, no solution

// Skip if current element too large
if(nums[i] + nums[i+1] + nums[i+2] > 0) break;

// Skip if current element too small  
if(nums[i] + nums[n-2] + nums[n-1] < 0) continue;
```

### **2. Efficient Duplicate Skipping:**
```cpp
// Skip duplicates immediately in outer loop
while(i < n-1 && nums[i] == nums[i+1]) i++;

// Bounds-safe duplicate skipping in inner loop
while(left < right && nums[left] == nums[left-1]) left++;
```

### **3. Target Transformation:**
```cpp
// Instead of checking nums[i] + nums[left] + nums[right] == 0
// Check nums[left] + nums[right] == -nums[i]
// Reduces computation in inner loop
```

## **⚡ Complexity Analysis**

### **Time Complexity:**
```
✅ OPTIMIZED APPROACH:
Overall: O(n²)
- Sorting: O(n log n)
- Outer loop: O(n)
- Inner two pointers: O(n) per iteration
- Total: O(n log n) + O(n²) = O(n²)

❌ BRUTE FORCE:
Time: O(n³) - three nested loops
Space: O(1) - no extra data structures
```

### **Space Complexity:**
```
✅ SPACE ANALYSIS:
- Sorting: O(1) if in-place, O(n) if creating new array
- Result storage: O(k) where k = number of valid triplets
- Additional variables: O(1)
- Total: O(1) auxiliary space (not counting output)
```

## **🧩 Problem Variations**

### **Type 1: 3Sum = 0 (Classic)**
```cpp
// Find all triplets that sum to zero
vector<vector<int>> threeSum(vector<int>& nums)
```

### **Type 2: 3Sum = Target**
```cpp
// Find all triplets that sum to specific target
vector<vector<int>> threeSum(vector<int>& nums, int target)
// Change: target = target - nums[i] (instead of -nums[i])
```

### **Type 3: 3Sum Closest**
```cpp
// Find triplet with sum closest to target
int threeSumClosest(vector<int>& nums, int target)
// Track minimum difference instead of exact match
```

### **Type 4: 3Sum Count**
```cpp
// Count number of valid triplets
int threeSumCount(vector<int>& nums)
// Increment counter instead of storing triplets
```

## **🎯 Decision Tree**

```
Need exactly 3 elements with sum condition?
├─ YES: Continue evaluation
└─ NO: Use different pattern

Array size reasonable (< 10⁴)?
├─ YES: 3Sum pattern applicable
└─ NO: Consider approximation algorithms

Duplicates allowed in result?
├─ NO: Use full duplicate handling (3 levels)
└─ YES: Simplified version without duplicate skipping

Want all triplets or just existence?
├─ All triplets: Return vector<vector<int>>
└─ Existence: Return bool, exit early on first match

Memory constraints?
├─ Tight: Optimize space, consider counting only
└─ Normal: Standard implementation with result storage
```

## **🔥 Similar Problems Using Same Pattern**

1. **4Sum** - Extend pattern: Fix two elements + Two pointers
2. **Two Sum** - Core building block (2 pointers on sorted)
3. **3Sum Closest** - Minimize difference instead of exact sum
4. **4Sum II** - Use hash map for half, iterate for other half
5. **Valid Triangle Number** - Three sides a ≤ b ≤ c where a+b > c
6. **3Sum With Multiplicity** - Count triplets with repetition allowed
7. **3Sum Smaller** - Count triplets with sum less than target

## **💡 Key Mental Models**

### **Problem Reduction Pattern:**
```
Think: "N-Sum = Fix one element + (N-1)-Sum"
3Sum = Fix first element + 2Sum problem
4Sum = Fix first element + 3Sum problem
Pattern extends to any N-Sum problem
```

### **Duplicate Prevention Mindset:**
```
Think: "Duplicates come from three sources"
1. Same fixed element processed multiple times
2. Same left value used in multiple pairs
3. Same right value used in multiple pairs
Must handle ALL three to prevent duplicate results
```

### **Two Pointers Movement Logic:**
```
sum < target: Move left pointer right (increase sum)
sum > target: Move right pointer left (decrease sum)
sum == target: Process result, move both pointers
Always skip duplicates after movement
```

## **🚨 Common Pitfalls**

### **1. Missing Duplicate Handling Levels**
```cpp
// ❌ WRONG: Only handle one level of duplicates
if(i > 0 && nums[i] == nums[i-1]) continue;  // Only outer loop

// ✅ CORRECT: Handle all three levels
// Outer loop + left pointer + right pointer duplicate handling
```

### **2. Incorrect Bounds in Duplicate Skipping**
```cpp
// ❌ WRONG: Bounds check after array access
while(nums[left] == nums[left-1] && left < right) left++;

// ✅ CORRECT: Bounds check before array access
while(left < right && nums[left] == nums[left-1]) left++;
```

### **3. Forgetting to Move Pointers After Match**
```cpp
// ❌ WRONG: Add result but don't move pointers (infinite loop)
if(sum == target) {
    result.push_back({nums[i], nums[left], nums[right]});
    // Missing: left++; right--;
}

// ✅ CORRECT: Always move both pointers after finding match
```

### **4. Wrong Direction in Duplicate Skipping**
```cpp
// ❌ WRONG: Skip while different (moves immediately)
while(nums[left] != nums[left-1]) left++;

// ✅ CORRECT: Skip while same (stays until different)
while(nums[left] == nums[left-1]) left++;
```

### **5. Temp Vector Management**
```cpp
// ❌ WRONG: Clear temp outside inner loop (accumulates values)
temp.clear();  // Outside while loop
while(left < right) {
    temp.push_back(...);  // Keeps growing!
}

// ✅ CORRECT: Clear temp for each triplet
if(sum == target) {
    temp.clear();  // Fresh for each triplet
    temp.push_back(...);
}
```

## **🎯 Debugging Checklist**

When 3Sum solution fails:
```
□ Array sorted before processing?
□ All three duplicate handling levels implemented?
□ Bounds checking in duplicate skipping (left < right first)?
□ Pointers moved after finding match (left++, right--)?
□ Outer loop bound correct (i < n-2, not i < n)?
□ Target calculation correct (-nums[i] for sum = 0)?
□ Temp vector cleared for each new triplet?
□ No array access before bounds validation?
□ Two pointers initialized correctly (left = i+1, right = n-1)?
□ While loop condition correct (left < right)?
```

## **🧪 Pattern Extension to N-Sum**

```cpp
// Pattern scales to any N-Sum problem:
// 2Sum: Two pointers on sorted array
// 3Sum: Fix one + 2Sum  
// 4Sum: Fix one + 3Sum
// kSum: Fix one + (k-1)Sum

// General approach:
if(k == 2) return twoSum(nums, target);
for(int i = 0; i < nums.size(); i++) {
    if(i > 0 && nums[i] == nums[i-1]) continue;
    auto subResult = kSum(subarray, k-1, target - nums[i]);
    // Add nums[i] to each result in subResult
}
```

---

## **🎯 Action Items**
- [ ] Master the "fix one + reduce" pattern mindset
- [ ] Practice all three levels of duplicate handling
- [ ] Understand two pointers movement logic thoroughly  
- [ ] Template the bounds-safe duplicate skipping
- [ ] Recognize when to extend pattern to 4Sum, kSum
- [ ] Debug systematically using the checklist approach
