# DSA Pattern: Pascal's Triangle

## 🎯 Pattern Recognition Triggers

### When to Use This Pattern:
```
✅ TRIGGER PHRASES:
- "Pascal's Triangle"
- "Binomial coefficients"
- "nCr / combinations"
- "Triangle where each element is sum of two above"
- "Row starts and ends with 1"
- "Generate triangular number patterns"

✅ PROBLEM STRUCTURE:
- Mathematical triangle structure
- Each element = sum of two elements directly above
- Edges always contain 1
- Need specific element or entire row/triangle
- Combinatorial mathematics involved
```

## 🔍 Pattern Recognition Checklist
```
□ Triangle-like structure mentioned?
□ Elements formed by summing adjacent elements above?
□ Binomial coefficients or nCr calculations needed?
□ Mathematical sequence with specific generation rule?
□ Optimization required for large numbers?

If ✅ → Use Pascal's Triangle Pattern!
```

## 📝 Core Mathematical Insights

### Key Relationship:
```
Pascal[r][c] = rCc = r! / (c! × (r-c)!)

Each element equals the number of ways to choose c items from r items.
```

### Triangle Structure:
```
Row 0:        1
Row 1:      1   1  
Row 2:    1   2   1
Row 3:  1   3   3   1
Row 4: 1  4   6   4  1

Pattern: Pascal[r][c] = Pascal[r-1][c-1] + Pascal[r-1][c]
```

## 🚨 Critical Index Conversion

### 1-Indexed vs 0-Indexed:
```cpp
// Problem often uses 1-indexed terminology
// Programming uses 0-indexed arrays

User Request: "Row r, Column c" (1-indexed)
Your Code: Calculate Pascal[r-1][c-1] (0-indexed)

Always convert: (user_r, user_c) → (r-1, c-1)
```

## 📝 Optimized Implementation Template

```cpp
class Solution {
public:
    int pascalTriangleElement(int r, int c) {
        // Convert 1-indexed to 0-indexed
        return nCr(r-1, c-1);
    }
    
private:
    int nCr(int n, int r) {
        // Optimization: choose smaller r for fewer iterations
        if(r > n - r) r = n - r;
        
        // Base cases
        if(r == 0) return 1;
        if(r == 1) return n;
        
        int result = 1;
        
        // Step-by-step calculation to avoid overflow
        for(int i = 0; i < r; i++) {
            result = result * (n - i) / (i + 1);
        }
        
        return result;
    }
};
```

## ⚡ Key Optimization Techniques

### 1. **Step-by-Step nCr Calculation**
```cpp
// ❌ BAD: Calculate full factorials (overflow risk)
return n! / (r! * (n-r)!);

// ✅ GOOD: Interleaved multiply and divide
for(int i = 0; i < r; i++) {
    result = result * (n-i) / (i+1);
}
```

### 2. **Choose Smaller r Value**
```cpp
// Optimization: nCr = nC(n-r)
// Calculate smaller computation
if(r > n-r) r = n-r;

// Example: 10C8 becomes 10C2 (much faster!)
```

### 3. **Overflow Prevention**
```cpp
// Multiply first, then divide in same step
// Keeps intermediate values smaller
result = result * numerator / denominator;
```

## ⚡ Complexity Analysis

### Single Element Query:
```
✅ OPTIMAL (Step-by-step nCr):
Time: O(min(r, n-r)) - Only r iterations
Space: O(1) - Only variables

❌ SUBOPTIMAL (Build entire triangle):
Time: O(r²) - Build all rows up to r
Space: O(r²) - Store entire triangle

❌ AVOID (Full factorial):
Time: O(n) - Calculate factorials
Space: O(1) - But overflow risk high
```

## 🧩 Problem Variations

### Type 1: Single Element
```cpp
// Get specific Pascal[r][c] value
return nCr(r-1, c-1);
```

### Type 2: Entire Row
```cpp
// Generate complete row r
vector<int> getRow(int rowIndex) {
    vector<int> row(rowIndex + 1);
    for(int c = 0; c <= rowIndex; c++) {
        row[c] = nCr(rowIndex, c);
    }
    return row;
}
```

### Type 3: Entire Triangle
```cpp
// Generate first numRows of Pascal's Triangle
vector<vector<int>> generate(int numRows) {
    vector<vector<int>> triangle(numRows);
    for(int r = 0; r < numRows; r++) {
        triangle[r] = getRow(r);
    }
    return triangle;
}
```

## 🎯 Decision Tree

```
Need Pascal's Triangle element?
├─ Single element: Use optimized nCr calculation
├─ Entire row: Calculate each nCr in the row  
└─ Entire triangle: Use dynamic programming approach

Large numbers involved?
├─ YES: Use step-by-step nCr (avoid overflow)
└─ NO: Direct calculation acceptable

Multiple queries?
├─ YES: Consider memoization or precomputation
└─ NO: Direct calculation per query
```

## 🔥 Similar Problems

1. **Pascal's Triangle II** - Return specific row
2. **Unique Paths** - Grid path counting (uses nCr)
3. **Binomial Coefficients** - Direct nCr calculations
4. **Catalan Numbers** - Related mathematical sequences
5. **Triangular Number Patterns** - Similar structure
6. **Combinations/Permutations** - Mathematical foundations

## 💡 Key Mental Models

### Mathematical Foundation:
```
Think: "How many ways to choose c items from r items?"
Not: "Build triangle and look up value"
```

### Index Conversion:
```
User's mental model: 1st, 2nd, 3rd... (natural counting)
Your code model: [0], [1], [2]... (array indexing)
Always subtract 1 from user input!
```

### Efficiency Mindset:
```
For single queries: Direct nCr calculation
For multiple queries: Consider building/caching
For large numbers: Step-by-step to avoid overflow
```

## 🚨 Common Pitfalls

### 1. **Index Confusion**
```cpp
// ❌ WRONG: Use user input directly
return nCr(r, c);

// ✅ CORRECT: Convert to 0-indexed
return nCr(r-1, c-1);
```

### 2. **Overflow in Factorial Approach**
```cpp
// ❌ WRONG: Calculate full factorials
int factorial(int n) { /* huge numbers! */ }

// ✅ CORRECT: Step-by-step calculation
result = result * (n-i) / (i+1);
```

### 3. **Inefficient Triangle Building**
```cpp
// ❌ WRONG: Build entire triangle for single element
// ✅ CORRECT: Direct nCr calculation for single queries
```

## 🎯 Debugging Checklist

When Pascal's Triangle solution fails:
```
□ Check index conversion (subtract 1 from user input)
□ Verify nCr calculation logic
□ Test with small examples (manually verify)
□ Check for integer overflow with large inputs
□ Ensure proper order of multiply/divide operations
□ Validate base cases (r=0, c=0, c=r)
```

---

## 🎯 Action Items
- [ ] Master the index conversion concept
- [ ] Practice step-by-step nCr calculation
- [ ] Understand when to use different approaches
- [ ] Template the optimized nCr function
- [ ] Test with both small and large inputs
