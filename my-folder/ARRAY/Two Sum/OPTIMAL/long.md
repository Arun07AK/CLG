# **DSA Pattern: Sort + Two Pointers for Two Sum**

## **🎯 Pattern Recognition Triggers**

### **When to Use This Pattern:**
```
✅ TRIGGER PHRASES:
- "Find TWO elements that sum to target"
- "Return indices of pair that adds up to X"
- "Two numbers with given sum"
- Array is unsorted BUT space constraints exist
- Want alternative to hash map approach
- Interview asks for "different approach"

✅ PROBLEM STRUCTURE:
- Array/list of numbers with indices needed
- Need exactly 2 elements that satisfy sum condition
- Space optimization preferred over time optimization
- Willing to sacrifice O(n) time for O(1) extra space
- Index preservation required during sorting
```

## **🔍 Pattern Recognition Checklist**
```
□ Two elements needed that sum to target?
□ Need to return original indices (not just values)?
□ Space constraints make hash map undesirable?
□ Array is unsorted (sorted arrays use direct two pointers)?
□ Interviewer asks for "space-optimized" approach?
□ Multiple approaches requested for same problem?

If ✅ → Use Sort + Two Pointers Pattern!
```

## **📝 Core Mathematical Insights**

### **Key Strategy:**
```
Transform unsorted search problem into sorted search problem:
1. Preserve original indices before sorting
2. Sort by values to enable two-pointers technique  
3. Use two-pointers on sorted values
4. Return original indices from preserved mapping
```

### **Index Preservation Technique:**
```
Original: [5, 2, 8, 1]  indices: [0, 1, 2, 3]
Preserve: [{5,0}, {2,1}, {8,2}, {1,3}]  // {value, original_index}
Sort:     [{1,3}, {2,1}, {5,0}, {8,2}]  // sorted by value
Search:   Use two pointers on sorted values
Return:   Original indices from preserved mapping
```

## **🚨 Critical Implementation Considerations**

### **Index Preservation Storage:**
```cpp
// Store {value, original_index} pairs before sorting
vector<vector<int>> eleIndex;
for(int i = 0; i < nums.size(); i++) {
    eleIndex.push_back({nums[i], i});
}
```

### **Two Pointers Boundary Condition:**
```cpp
// CRITICAL: Use left < right (not left <= right)
while(left < right) {  // Prevents same element used twice
    // comparison logic
}
```

## **📝 Optimized Implementation Template**

```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int n = nums.size();
        vector<vector<int>> eleIndex;
        
        // Step 1: Preserve original indices
        for(int i = 0; i < n; i++) {
            eleIndex.push_back({nums[i], i});
        }
        
        // Step 2: Sort by values while preserving indices
        sort(eleIndex.begin(), eleIndex.end(), 
             [](const vector<int>& a, const vector<int>& b) {
                 return a[0] < b[0];  // Sort by value (first element)
             });
        
        // Step 3: Two pointers search on sorted values
        int left = 0, right = n - 1;
        while(left < right) {
            int sum = eleIndex[left][0] + eleIndex[right][0];
            
            if(sum == target) {
                // Return original indices in increasing order
                int idx1 = eleIndex[left][1];
                int idx2 = eleIndex[right][1];
                return {min(idx1, idx2), max(idx1, idx2)};
            }
            else if(sum < target) {
                left++;   // Need larger sum
            }
            else {
                right--;  // Need smaller sum
            }
        }
        
        return {-1, -1};  // No solution found
    }
};
```

## **⚡ Complexity Analysis**

### **Sort + Two Pointers Approach:**
```
❌ SUBOPTIMAL for general Two Sum:
Time: O(n log n) - Dominated by sorting step
Space: O(n) - For index preservation array

Breakdown:
- Index preservation: O(n) time, O(n) space
- Sorting: O(n log n) time, O(1) additional space
- Two pointers search: O(n) time, O(1) space
```

### **Comparison with Hash Map:**
```
✅ HASH MAP (Optimal):
Time: O(n), Space: O(n)

❌ SORT + TWO POINTERS:  
Time: O(n log n), Space: O(n)

Trade-off: Worse time complexity, same space complexity
```

## **🧩 When This Pattern is Actually Beneficial**

### **Scenario 1: Space-Constrained with Pre-sorted Data**
```cpp
// If array comes pre-sorted, skip sorting step
// Time becomes O(n), Space becomes O(1)
// Superior to hash map in this specific case
```

### **Scenario 2: Multiple Two Sum Queries**
```cpp
// Sort once, answer multiple queries
// Amortized time improvement for many queries
```

### **Scenario 3: Interview Diversity**
```cpp
// Demonstrates knowledge of multiple approaches
// Shows understanding of time/space trade-offs
```

## **🎯 Decision Tree**

```
Array already sorted?
├─ YES: Use direct two pointers (O(n) time, O(1) space)
└─ NO: Continue evaluation

Space extremely constrained AND few elements?
├─ YES: Consider sort + two pointers  
└─ NO: Use hash map approach

Multiple queries on same array?
├─ YES: Sort once, use two pointers for each query
└─ NO: Hash map approach preferred

Interviewer asks for alternative approach?
├─ YES: Demonstrate sort + two pointers knowledge
└─ NO: Stick with optimal hash map approach
```

## **🔥 Similar Problems Using Same Pattern**

1. **Two Sum II (Sorted Array)** - Direct two pointers without sorting
2. **3Sum** - Fix one element, two pointers on remaining
3. **4Sum** - Fix two elements, two pointers on remaining  
4. **Two Sum - Closest to Target** - Minimize difference instead of exact match
5. **Container With Most Water** - Two pointers optimization
6. **Trapping Rain Water** - Two pointers technique application
7. **Valid Triangle Number** - Count valid triangles using sorted approach

## **💡 Key Mental Models**

### **Index Bookkeeping:**
```
Think: "Before I lose track of original positions, let me attach ID tags"
Process: Tag → Sort → Search → Return original IDs
```

### **Two Pointers Movement Logic:**
```
sum < target: Move left pointer right (increase sum)
sum > target: Move right pointer left (decrease sum)  
sum == target: Found the answer
```

### **Boundary Understanding:**
```
left < right: Different elements (required)
left == right: Same element twice (forbidden)
left > right: Crossed pointers (search exhausted)
```

## **🚨 Common Pitfalls**

### **1. Wrong Loop Condition**
```cpp
// ❌ WRONG: Allows same element twice
while(left <= right) { /* can use same element */ }

// ✅ CORRECT: Ensures different elements
while(left < right) { /* different elements only */ }
```

### **2. Index Access Confusion**
```cpp
// ❌ WRONG: Accessing wrong array elements
eleIndex[i][0]  // Value (correct for comparison)
eleIndex[i][1]  // Original index (correct for return)

// Mix-up leads to wrong results
```

### **3. Sort Comparator Errors**
```cpp
// ❌ WRONG: Missing reference in lambda
[](const vector<int> a, const vector<int> b)  // Copies (slow)

// ✅ CORRECT: Use references
[](const vector<int>& a, const vector<int>& b)  // Fast
```

### **4. Return Order Issues**
```cpp
// ❌ POTENTIAL ISSUE: May not be in increasing order
return {eleIndex[left][1], eleIndex[right][1]};

// ✅ SAFE: Guarantee increasing order
int idx1 = eleIndex[left][1], idx2 = eleIndex[right][1];
return {min(idx1, idx2), max(idx1, idx2)};
```

## **🎯 Debugging Checklist**

When Sort + Two Pointers solution fails:
```
□ Check loop condition (left < right, not <=)
□ Verify index preservation logic (storing {value, index})
□ Confirm sort comparator syntax (const vector<int>&)
□ Validate element access (eleIndex[i][0] vs eleIndex[i][1])
□ Test return order (indices in increasing order)
□ Trace two pointers movement logic
□ Verify no same-element-twice usage
□ Check boundary conditions (empty array, single element)
```

## **🧪 Pattern Trade-off Analysis**

```
✅ WHEN TO USE:
- Demonstrating multiple approaches in interviews
- Array comes pre-sorted (skip sorting step)
- Multiple queries on same dataset
- Learning two pointers technique

❌ WHEN TO AVOID:
- General Two Sum optimization (hash map better)
- Time complexity is critical
- Single query on unsorted array
- Space complexity same as optimal solution
```

---

## **🎯 Action Items**
- [ ] Understand when this pattern is truly beneficial vs hash map
- [ ] Master index preservation technique with {value, index} pairs  
- [ ] Practice custom sort with lambda comparators
- [ ] Remember boundary condition: left < right (not <=)
- [ ] Recognize this as suboptimal but educational approach
- [ ] Use for interview diversity, not as primary solution
