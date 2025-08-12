# DSA Pattern: Matrix Rotation

## 🎯 Pattern Recognition Triggers

### When to Use This Pattern:
```
✅ TRIGGER PHRASES:
- "Rotate matrix by 90 degrees"
- "Clockwise/counter-clockwise rotation"
- "Transform matrix orientation"
- "Matrix image rotation"
- "Grid rotation problems"
- "2D array transformation"

✅ PROBLEM STRUCTURE:
- Square N×N matrix manipulation
- Need to change element positions systematically
- Geometric transformation requirements
- Image/grid processing problems
- In-place or space-optimized solutions needed
```

## 🔍 Pattern Recognition Checklist
```
□ Square matrix involved (N×N)?
□ Need to rotate elements by specific degrees?
□ Geometric transformation required?
□ Position mapping between old and new coordinates?
□ Space complexity constraints mentioned?

If ✅ → Use Matrix Rotation Pattern!
```

## 📐 Core Mathematical Foundation

### 90° Clockwise Rotation Transformation:
```
Original position (i, j) → New position (j, n-1-i)

Example for 3×3:
(0,0)→(0,2)  (0,1)→(1,2)  (0,2)→(2,2)
(1,0)→(0,1)  (1,1)→(1,1)  (1,2)→(2,1)
(2,0)→(0,0)  (2,1)→(1,0)  (2,2)→(2,0)
```

### Visual Transformation:
```
Original:      90° Clockwise:
[1 2 3]        [7 4 1]
[4 5 6]   →    [8 5 2]
[7 8 9]        [9 6 3]
```

## 📝 Implementation Approaches

### **Approach 1: Column-to-Row Transformation (Intuitive)**
```cpp
vector<vector<int>> rotateMatrix(vector<vector<int>>& matrix) {
    int n = matrix.size();
    vector<vector<int>> result(n, vector<int>(n));
    
    // Read each column from bottom to top, make it a row
    for(int i = 0; i < n; i++) {           // For each column i
        for(int j = n-1; j >= 0; j--) {    // Read bottom to top
            result[i][n-1-j] = matrix[j][i];
        }
    }
    return result;
}
```

### **Approach 2: Direct Position Mapping (Mathematical)**
```cpp
vector<vector<int>> rotateMatrix(vector<vector<int>>& matrix) {
    int n = matrix.size();
    vector<vector<int>> rotated(n, vector<int>(n, 0));
    
    // Apply transformation formula directly
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            rotated[j][n - i - 1] = matrix[i][j];
        }
    }
    return rotated;
}
```

### **Approach 3: In-Place Rotation (Space Optimized)**
```cpp
void rotateMatrix(vector<vector<int>>& matrix) {
    int n = matrix.size();
    
    // Step 1: Transpose matrix (swap across diagonal)
    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            swap(matrix[i][j], matrix[j][i]);
        }
    }
    
    // Step 2: Reverse each row
    for(int i = 0; i < n; i++) {
        reverse(matrix[i].begin(), matrix[i].end());
    }
}
```

### **Approach 4: Pseudo In-Place (Modify Original)**
```cpp
void rotateMatrix(vector<vector<int>>& matrix) {
    int n = matrix.size();
    vector<vector<int>> temp(n, vector<int>(n, 0));
    
    // Create rotated version
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            temp[j][n - i - 1] = matrix[i][j];
        }
    }
    
    // Copy back to original
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            matrix[i][j] = temp[i][j];
        }
    }
}
```

## ⚡ Complexity Analysis

### Space-Time Trade-offs:
```
Approach 1 (Column-to-Row):
✅ Time: O(n²) - Single pass through matrix
✅ Space: O(n²) - New result matrix
✅ Readability: High (intuitive logic)

Approach 2 (Direct Mapping):
✅ Time: O(n²) - Single pass through matrix
✅ Space: O(n²) - New rotated matrix
✅ Readability: Medium (formula-based)

Approach 3 (True In-Place):
✅ Time: O(n²) - Two passes (transpose + reverse)
✅ Space: O(1) - No extra space
✅ Memory: Most efficient

Approach 4 (Pseudo In-Place):
✅ Time: O(n²) - Single pass + copy
✅ Space: O(n²) - Temporary matrix
✅ Behavior: Modifies original matrix
```

## 🔄 Rotation Variations

### 90° Counter-Clockwise:
```cpp
// Method 1: Reverse rows first, then transpose
// Method 2: Direct formula: (i,j) → (n-1-j, i)
```

### 180° Rotation:
```cpp
// Method 1: Apply 90° rotation twice
// Method 2: Direct formula: (i,j) → (n-1-i, n-1-j)
```

### 270° Clockwise (= 90° Counter-clockwise):
```cpp
// Apply 90° clockwise rotation three times
// Or use counter-clockwise formulas
```

## 🎯 Decision Tree

```
Need matrix rotation?
├─ Return new matrix: Use Approach 1 or 2
├─ Modify original matrix: Use Approach 4
└─ Memory constrained: Use Approach 3 (true in-place)

Multiple rotations needed?
├─ YES: Consider caching or optimizing rotation count
└─ NO: Direct single rotation

Large matrices?
├─ YES: Prefer in-place rotation (Approach 3)
└─ NO: Any approach acceptable

Code readability priority?
├─ YES: Use Approach 1 (column-to-row)
└─ NO: Use most efficient approach for constraints
```

## 🧩 Key Mental Models

### Column-to-Row Thinking:
```
"Take column i, read from bottom to top, make it row i"
- Visual and intuitive
- Easy to trace and debug
- Natural for image processing thinking
```

### Mathematical Transformation:
```
"Apply position formula: (i,j) → (j, n-1-i)"
- Direct and systematic
- Generalizes to other transformations
- Efficient implementation
```

### Two-Step Process:
```
"Transpose + Reverse = 90° Clockwise Rotation"
- Breaks complex operation into simple steps
- Memory efficient
- Reusable for other transformations
```

## 🔥 Similar Problems

1. **Rotate Image** - Standard 90° matrix rotation
2. **Spiral Matrix** - Layer-by-layer matrix traversal
3. **Matrix Transpose** - Diagonal reflection
4. **Flip Matrix Horizontally/Vertically** - Row/column reversal
5. **Matrix Layer Rotation** - Rotate specific matrix layers
6. **Image Processing** - Geometric transformations
7. **Game Board Rotations** - Tetris, puzzle games

## 🚨 Common Pitfalls

### 1. **Index Boundary Errors**
```cpp
// ❌ WRONG: Going beyond matrix bounds
for(int i = 0; i <= n; i++)

// ✅ CORRECT: Proper boundary
for(int i = 0; i < n; i++)
```

### 2. **Position Mapping Mistakes**
```cpp
// ❌ WRONG: Incorrect transformation
rotated[i][j] = matrix[i][j];

// ✅ CORRECT: Proper 90° clockwise mapping
rotated[j][n-1-i] = matrix[i][j];
```

### 3. **In-Place Overwriting Issues**
```cpp
// ❌ WRONG: Direct assignment loses data
matrix[j][n-1-i] = matrix[i][j];  // Overwrites needed values

// ✅ CORRECT: Use temporary space or careful swapping
```

### 4. **Return Type Confusion**
```cpp
// ❌ WRONG: Return type mismatch
void rotateMatrix(...) {
    return result;  // Can't return from void
}

// ✅ CORRECT: Match return type with behavior
vector<vector<int>> rotateMatrix(...) // OR void for in-place
```

## 💡 Optimization Techniques

### 1. **Choose Optimal Approach by Constraints**
```cpp
// Memory critical: Use true in-place (transpose + reverse)
// Readability critical: Use column-to-row approach
// Performance critical: Use direct mapping
```

### 2. **Rotation Count Optimization**
```cpp
// Multiple rotations: Optimize count
int rotations = count % 4;  // 4 rotations = original
```

### 3. **Cache-Friendly Access Patterns**
```cpp
// Consider memory access patterns for large matrices
// Row-major vs column-major considerations
```

## 🎯 Debugging Checklist

When matrix rotation fails:
```
□ Check transformation formula correctness
□ Verify loop boundaries (0 to n-1, not n)
□ Ensure proper index ordering (i,j vs j,i)
□ Test with small 2×2 or 3×3 examples
□ Trace through position mappings manually
□ Check return type matches function behavior
□ Verify no array bounds violations
□ Test edge cases (1×1, 2×2 matrices)
```

## 📊 Pattern Benefits

- **Versatile**: Works for various rotation angles
- **Scalable**: Handles different matrix sizes
- **Flexible**: Multiple implementation strategies
- **Optimizable**: Can prioritize space vs time
- **Reusable**: Core concepts apply to many problems

---

## 🎯 Action Items
- [ ] Master the position transformation formula
- [ ] Practice all four implementation approaches
- [ ] Understand space-time trade-offs for each method
- [ ] Template preferred approach for quick implementation
- [ ] Practice with different rotation angles and directions
