# DSA Pattern: Two-Pointer Position Tracking

## 🎯 Pattern Recognition Triggers

### When to Use This Pattern:
```
✅ TRIGGER PHRASES:
- "Rearrange array elements"
- "Alternating placement" 
- "Even/odd positions"
- "Maintain relative order within groups"
- "Place elements of type A at positions X, type B at positions Y"

✅ PROBLEM STRUCTURE:
- Input has exactly 2 types of elements
- Output requires specific positional arrangement
- Need to preserve order within each type
- Predictable position pattern (alternating, even/odd, etc.)
```

## 🔍 Pattern Recognition Checklist
```
□ Two distinct element types?
□ Specific output position requirements?
□ Need to preserve relative order within types?
□ Alternating or predictable placement pattern?

If all ✅ → Use Two-Pointer Position Tracking!
```

## 📝 Code Template

```cpp
// Two-Pointer Position Tracking Template
vector<int> rearrangePattern(vector<int>& nums) {
    vector<int> result(nums.size());
    
    int pointer1 = startPos1;  // Track positions for type 1
    int pointer2 = startPos2;  // Track positions for type 2
    
    for(int i = 0; i < nums.size(); i++) {
        if(isType1(nums[i])) {
            result[pointer1] = nums[i];
            pointer1 += step1;
        }
        else {
            result[pointer2] = nums[i];
            pointer2 += step2;
        }
    }
    
    return result;
}
```

## 🧩 Common Variations

### Alternating Pattern (pos-neg-pos-neg):
```cpp
int posIndex = 0;  // Positions: 0, 2, 4, 6...
int negIndex = 1;  // Positions: 1, 3, 5, 7...
// Increment: +2 for both
```

### Block Pattern (all type1, then all type2):
```cpp
int type1Index = 0;           // Positions: 0, 1, 2...
int type2Index = type1Count;  // Positions: k, k+1, k+2...
// Increment: +1 for both
```

### Even-Odd Pattern:
```cpp
int evenIndex = 0;  // Positions: 0, 2, 4...
int oddIndex = 1;   // Positions: 1, 3, 5...
// Increment: +2 for both
```

## ⚡ Complexity Analysis
```
✅ OPTIMAL:
Time: O(n) - Single pass through input
Space: O(n) - Result array only

❌ AVOID:
Time: O(n²) - Repeated searching
Space: O(n) + extra tracking structures
```

## 🎯 Decision Tree

```
Problem involves rearranging array?
├─ YES: Continue
└─ NO: Different pattern

Elements have exactly 2 types/categories?
├─ YES: Continue  
└─ NO: Consider multi-pointer or bucket sort

Output has predictable position pattern?
├─ YES: Use position tracking pointers ✅
└─ NO: Consider sorting + post-processing

Need to maintain relative order within types?
├─ YES: Single pass with direct placement ✅
└─ NO: Consider simpler sorting approaches
```

## 🔥 Similar Problems

1. **Rearrange Array Elements by Sign** - pos/neg alternating
2. **Sort Array by Parity** - even/odd separation
3. **Move Zeros** - zeros to end, maintain order
4. **Partition Array** - elements around pivot
5. **Squares of Sorted Array** - merge from both ends

## 💡 Key Mental Shift

**❌ Instead of:** "How do I search for elements to place?"
**✅ Think:** "Where should each element type go, and how do I track those positions?"

**This shifts from O(n²) searching to O(n) direct placement!**

## 📊 Pattern Benefits

- **Efficiency**: Single pass, O(n) time
- **Simplicity**: No complex searching logic
- **Maintainability**: Clear separation of concerns
- **Scalability**: Easy to extend to more types with more pointers

---

## 🎯 Action Items
- [ ] Practice identifying the 2-type element structure
- [ ] Look for position pattern requirements in problem statements
- [ ] Template this approach for quick implementation
- [ ] Verify complexity expectations match O(n) time, O(n) space
