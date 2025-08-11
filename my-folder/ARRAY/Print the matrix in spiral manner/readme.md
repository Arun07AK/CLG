# DSA Pattern: Spiral Matrix Traversal

## 🎯 Pattern Recognition Triggers

### When to Use This Pattern:
```
✅ TRIGGER PHRASES:
- "Spiral order" / "Clockwise spiral"
- "Print matrix in spiral manner"
- "Traverse matrix layer by layer"
- "Outer to inner traversal"
- "Matrix boundary traversal"

✅ PROBLEM STRUCTURE:
- 2D matrix/grid traversal required
- Need to visit elements in specific order (usually spiral)
- Layer-by-layer processing pattern
- Boundary-aware navigation needed
```

## 🔍 Pattern Recognition Checklist
```
□ 2D matrix/grid involved?
□ Need to traverse in spiral/layer-by-layer order?
□ Elements should be visited exactly once?
□ Boundary management required?
□ Clockwise or counter-clockwise movement pattern?

If ✅ → Use Spiral Matrix Traversal Pattern!
```

## 📝 Code Template

```cpp
// Spiral Matrix Traversal Template
vector<int> spiralOrder(vector<vector<int>>& matrix) {
    if(matrix.empty() || matrix[0].empty()) return {};
    
    vector<int> result;
    int top = 0;
    int bottom = matrix.size() - 1;
    int left = 0;
    int right = matrix[0].size() - 1;
    
    while(top <= bottom && left <= right) {
        // Direction 1: RIGHT (left to right on top row)
        for(int i = left; i <= right; i++) {
            result.push_back(matrix[top][i]);
        }
        top++;
        
        // Direction 2: DOWN (top to bottom on right column)
        for(int i = top; i <= bottom; i++) {
            result.push_back(matrix[i][right]);
        }
        right--;
        
        // Direction 3: LEFT (right to left on bottom row)
        if(top <= bottom) {  // Boundary check for edge cases
            for(int i = right; i >= left; i--) {
                result.push_back(matrix[bottom][i]);
            }
            bottom--;
        }
        
        // Direction 4: UP (bottom to top on left column)
        if(left <= right) {  // Boundary check for edge cases
            for(int i = bottom; i >= top; i--) {
                result.push_back(matrix[i][left]);
            }
            left++;
        }
    }
    
    return result;
}
```

## 🧩 Direction & Boundary Pattern

### Four-Direction Cycle:
```cpp
1. RIGHT: row=top,    col: left→right,  then top++
2. DOWN:  col=right,  row: top→bottom,  then right--
3. LEFT:  row=bottom, col: right→left,  then bottom--
4. UP:    col=left,   row: bottom→top,  then left++
```

### Boundary Shrinking Logic:
```
After each direction, "consume" the traversed boundary:
- RIGHT consumes top row    → top++
- DOWN consumes right col   → right--
- LEFT consumes bottom row  → bottom--
- UP consumes left col      → left++
```

## ⚡ Complexity Analysis
```
✅ OPTIMAL:
Time: O(m×n) - Visit each element exactly once
Space: O(1) - Only boundary variables (excluding output array)

❌ AVOID:
Time: O(m×n×k) - Multiple passes or redundant checks
Space: O(m×n) - Extra tracking matrices
```

## 🚨 Critical Edge Cases & Pitfalls

### 1. **Boundary Checks Before LEFT and UP**
```cpp
// ❌ WRONG - Can cause duplicates or invalid access
for(int i = right; i >= left; i--) {  // Always executes
    result.push_back(matrix[bottom][i]);
}

// ✅ CORRECT - Check if valid rows exist
if(top <= bottom) {  // Only execute if rows remain
    for(int i = right; i >= left; i--) {
        result.push_back(matrix[bottom][i]);
    }
    bottom--;
}
```

### 2. **While Condition Must Use AND (&&)**
```cpp
// ❌ WRONG - OR allows invalid combinations
while(top <= bottom || left <= right)

// ✅ CORRECT - Need BOTH valid rows AND columns
while(top <= bottom && left <= right)
```

### 3. **Single Row/Column Matrices**
```
Single row: [[1,2,3,4]] → Only RIGHT direction valid
Single col: [[1],[2],[3]] → Only RIGHT + DOWN valid
Without boundary checks → Duplicates elements!
```

## 🎯 Decision Tree

```
Problem involves 2D matrix traversal?
├─ YES: Continue
└─ NO: Different pattern

Need spiral/layer-by-layer order?
├─ YES: Continue
└─ NO: Consider row-wise/column-wise traversal

Clockwise or counter-clockwise?
├─ Clockwise: Use standard template
└─ Counter-clockwise: Reverse direction order

Need to modify or just read?
├─ Read only: Standard spiral traversal
└─ Modify: Consider spiral generation pattern
```

## 🔥 Similar Problems

1. **Spiral Matrix II** - Generate spiral matrix
2. **Rotate Image** - 90-degree matrix rotation
3. **Matrix Layer Rotation** - Rotate specific layers
4. **Diagonal Traverse** - Diagonal matrix traversal
5. **Snail Traversal** - Similar spiral patterns
6. **Matrix Border Traversal** - Boundary-only traversal

## 💡 Key Mental Models

### Boundary Shrinking Visualization:
```
Initial:     After RIGHT:   After DOWN:    After LEFT:
┌─────────┐  ┌─────────┐   ┌─────────┐   ┌─────────┐
│ T T T T │  │ x x x x │   │ x x x x │   │ x x x x │
│ L     R │  │ L     R │   │ L     R │   │ L     R │
│ L     R │  │ L     R │   │ L     R │   │ L     R │
│ B B B B │  │ B B B B │   │ B B B R │   │ x x x R │
└─────────┘  └─────────┘   └─────────┘   └─────────┘
```

### Direction State Machine:
```
RIGHT → DOWN → LEFT → UP → RIGHT (repeat until boundaries meet)
```

## 🎯 Debugging Checklist

When your spiral traversal fails:
```
□ Check if using && (not ||) in while condition
□ Verify boundary updates after each direction
□ Ensure LEFT direction has if(top <= bottom) check
□ Ensure UP direction has if(left <= right) check
□ Confirm matrix access uses [row][col] format
□ Test with single row/column matrices
□ Trace through small 2x2 or 3x3 examples
```

## 📊 Pattern Benefits

- **Systematic**: Clear 4-direction cycle
- **Boundary-aware**: Handles all matrix sizes
- **Optimal**: Single pass through all elements
- **Extensible**: Easy to modify for variations
- **Debuggable**: Clear state at each step

---

## 🎯 Action Items
- [ ] Practice with different matrix dimensions
- [ ] Understand the critical boundary checks
- [ ] Master the 4-direction boundary update pattern
- [ ] Template this approach for quick implementation
- [ ] Test edge cases: 1x1, 1xN, Nx1 matrices
