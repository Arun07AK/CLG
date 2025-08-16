# **DSA Pattern: Two Sum & Hash Map Complement Pattern**

## **🎯 Pattern Recognition Triggers**

### **When to Use This Pattern:**
```
✅ TRIGGER PHRASES:
- "Find TWO elements that sum to target"
- "Return indices of elements that add up to X"
- "Find pair with given sum"
- "Two numbers that equal target"
- "Complement" or "difference" mentioned
- "Have I seen this value before?"

✅ PROBLEM STRUCTURE:
- Array/list of numbers provided
- Need to find exactly 2 elements
- Elements must satisfy: element1 + element2 = target
- Return indices (not values) typically required
- Each element used at most once
- Linear scan with lookup optimization possible
```

## **🔍 Pattern Recognition Checklist**
```
□ Looking for exactly TWO elements?
□ Elements need to sum to a target value?
□ Need to return indices rather than values?
□ Array is unsorted (sorted arrays suggest two-pointers)?
□ Single pass solution desired for efficiency?
□ Space trade-off acceptable for time optimization?

If ✅ → Use Hash Map Complement Pattern!
```

## **📝 Core Mathematical Insights**

### **Key Relationship:**
```
For any target and current element:
needed_complement = target - current_element

If complement exists in our "memory":
  → We found the pair!
If complement doesn't exist:
  → Store current element for future lookups
```

### **Optimization Insight:**
```
Brute Force: Check current element against ALL remaining elements
Smart Approach: Check current element against ONLY its complement

Transform: O(n) search → O(1) lookup using hash map
```

## **🚨 Critical Implementation Details**

### **Storage vs Lookup Logic:**
```cpp
// STORE: Current element with its index
map[nums[i]] = i;

// LOOKUP: Search for the needed complement  
int complement = target - nums[i];
if(map.find(complement) != map.end()) {
    // Found it!
}
```

### **Index Order Convention:**
```cpp
// Return indices in increasing order
// Earlier index first, current index second
return {map[complement], i};  // old_index < current_index
```

## **📝 Optimized Implementation Template**

```cpp
#include <unordered_map>
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> seen;  // value → index mapping
        
        for(int i = 0; i < nums.size(); i++) {
            int complement = target - nums[i];
            
            // Check if complement exists in our memory
            if(seen.find(complement) != seen.end()) {
                return {seen[complement], i};  // old_index, current_index
            }
            
            // Store current element for future complement searches
            seen[nums[i]] = i;
        }
        
        return {-1, -1};  // No solution found (shouldn't happen per problem)
    }
};
```

## **⚡ Key Optimization Techniques**

### **1. Hash Map Existence Check Methods:**
```cpp
// Method 1: Most common, explicit check
if(map.find(key) != map.end()) { /* found */ }

// Method 2: Shorter syntax
if(map.count(key)) { /* found */ }

// Method 3: C++20 and later
if(map.contains(key)) { /* found */ }
```

### **2. Single Pass Algorithm:**
```cpp
// ✅ OPTIMAL: Build map while searching
// Check first, then store if not found

// ❌ SUBOPTIMAL: Two passes
// Pass 1: Build entire map
// Pass 2: Search for complements
```

### **3. Memory-Efficient Storage:**
```cpp
// Store only what we need for future lookups
// Don't store everything upfront
// Progressive building saves early termination
```

## **⚡ Complexity Analysis**

### **Hash Map Approach:**
```
✅ OPTIMAL:
Time: O(n) - Single pass through array
Space: O(n) - Store up to n elements in hash map
Best case: O(1) if answer found immediately

✅ Hash operations:
Average case: O(1) per lookup/insert
Worst case: O(n) per operation (rare collision)
```

### **Brute Force Comparison:**
```
❌ BRUTE FORCE:
Time: O(n²) - Nested loops check all pairs
Space: O(1) - No extra data structure

Trade-off: Space for significant time improvement
```

## **🧩 Problem Variations**

### **Type 1: Basic Two Sum**
```cpp
// Find indices of two elements that sum to target
return {index1, index2};
```

### **Type 2: Two Sum - Return Values**
```cpp
// Return the actual values instead of indices
return {nums[index1], nums[index2]};
```

### **Type 3: Two Sum - All Pairs**
```cpp
// Find all pairs that sum to target (handle duplicates)
vector<vector<int>> allPairs;
// Collect all valid pairs, avoid duplicates
```

### **Type 4: Two Sum - Count Pairs**
```cpp
// Count how many valid pairs exist
int count = 0;
// Count instead of returning first pair
```

## **🎯 Decision Tree**

```
Array sorted?
├─ YES: Consider two-pointers approach (O(1) space)
└─ NO: Hash map approach recommended

Need all pairs or just one?
├─ All pairs: Modify template, handle duplicates
└─ First pair: Use standard template

Multiple queries on same array?
├─ YES: Pre-build hash map, reuse for queries
└─ NO: Build map during single pass

Memory constraints?
├─ Tight: Consider two-pointers if array can be sorted
└─ Normal: Hash map is optimal choice
```

## **🔥 Similar Problems Using Same Pattern**

1. **Two Sum II (Sorted Array)** - Can use two-pointers alternative
2. **3Sum** - Expand to three elements (fix one, two-sum on rest)
3. **4Sum** - Further expansion of the concept
4. **Contains Duplicate** - Existence check with hash map
5. **Valid Anagram** - Character frequency with hash map
6. **Group Anagrams** - Hash map for categorization
7. **First Unique Character** - Frequency counting pattern
8. **Intersection of Two Arrays** - Set operations with hash

## **💡 Key Mental Models**

### **The Memory Bank Analogy:**
```
Think: Hash map as a "memory bank"
- Deposit: Store each number with its index as you see it
- Withdraw: Ask "Have I seen the complement before?"
- Transaction: Instant lookup instead of manual search
```

### **The Progressive Discovery:**
```
Don't think: "Build complete map then search"
Think: "Search as I build, stop when found"
```

### **The Complement Mindset:**
```
For each number, ask: "What number would complete this pair?"
Not: "What numbers could this pair with?"
```

## **🚨 Common Pitfalls**

### **1. Wrong Storage Logic**
```cpp
// ❌ WRONG: Store the complement
map[target - nums[i]] = i;

// ✅ CORRECT: Store the current element
map[nums[i]] = i;
```

### **2. Index Order Confusion**
```cpp
// ❌ WRONG: May violate increasing order requirement
return {i, map[complement]};

// ✅ CORRECT: Guarantees earlier index first
return {map[complement], i};
```

### **3. Premature Map Access**
```cpp
// ❌ WRONG: Creates entry if key doesn't exist
if(map[key] != 0) { /* dangerous */ }

// ✅ CORRECT: Check existence first
if(map.find(key) != map.end()) { /* safe */ }
```

### **4. Overcomplicating with Sorting**
```cpp
// ❌ UNNECESSARY: Sorting changes indices
sort(nums.begin(), nums.end());  // Loses original indices!

// ✅ CORRECT: Work with original array order
// Hash map handles unsorted data efficiently
```

## **🎯 Debugging Checklist**

When Two Sum solution fails:
```
□ Check what you're storing (current element, not complement)
□ Verify what you're searching for (complement, not element)
□ Confirm return order (earlier index first)
□ Test existence check logic (don't access non-existent keys)
□ Validate with simple example manually
□ Check edge cases (duplicate values, negative numbers)
□ Ensure single pass logic (don't search twice)
□ Verify map operations (find vs count vs direct access)
```

## **🧪 Quick Pattern Test Cases**

```cpp
// Test 1: Basic case
nums = [2, 7, 11, 15], target = 9
Expected: [0, 1] (2 + 7 = 9)

// Test 2: Negative numbers  
nums = [1, 3, -1, 2], target = 2
Expected: [0, 2] (1 + (-1) = 0... wait, 1 + 1 = 2)

// Test 3: Duplicates
nums = [3, 3], target = 6  
Expected: [0, 1] (3 + 3 = 6)

// Test 4: Large target
nums = [1, 2, 3, 4], target = 7
Expected: [2, 3] (3 + 4 = 7)
```

---

## **🎯 Action Items**
- [ ] Master the complement thinking pattern
- [ ] Practice hash map existence checks in C++
- [ ] Understand index ordering requirements
- [ ] Template the single-pass algorithm
- [ ] Debug with manual traces on small examples
- [ ] Recognize when NOT to use this pattern (sorted arrays)
