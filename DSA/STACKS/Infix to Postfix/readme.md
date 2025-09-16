# Infix to Postfix Conversion - Expert DSA Notes

## 1. Problem Statement
Convert mathematical expressions from infix notation (operator between operands) to postfix notation (operator after operands).
- **Input:** Infix expression string (e.g., "a+b*c")
- **Output:** Postfix expression string (e.g., "abc*+")
- **Constraints:** Valid operators (+, -, *, /, ^), operands (a-z, A-Z, 0-9), parentheses

## 2. Intuition and Explanation
- **Core Idea:** Use stack to temporarily hold operators while respecting precedence rules
- **Key Insight:** Higher precedence operators must appear later in postfix (evaluated first)
- **Stack Role:** Delays operator output until proper evaluation order is achieved
- **Parentheses:** Create barriers that override normal precedence rules

## 3. Approaches

### Approach 1: Shunting-Yard Algorithm (Optimal)
**Pros:**
- Single pass solution
- Handles all cases: precedence, associativity, parentheses
- Intuitive stack-based approach

**Cons:**
- Requires understanding of operator precedence and associativity rules

### Approach 2: Recursive Descent Parser
**Pros:**
- Clear recursive structure
- Easy to extend for complex grammars

**Cons:**
- More complex implementation
- Higher space complexity due to recursion

## 4. Complexity Analysis

### Shunting-Yard Algorithm:
- **Time:** O(n) - each character processed once
- **Space:** O(n) - stack can hold up to n operators

### Recursive Approach:
- **Time:** O(n) - each character processed once  
- **Space:** O(n) - recursion depth in worst case

## 5. Step-by-Step Example

**Input:** `"a+b*c"`

| Step | Char | Action | Stack | Output |
|------|------|--------|-------|--------|
| 1 | a | Operand | [] | "a" |
| 2 | + | Operator | [+] | "a" |
| 3 | b | Operand | [+] | "ab" |
| 4 | * | Higher prec | [+,*] | "ab" |
| 5 | c | Operand | [+,*] | "abc" |
| 6 | End | Pop all | [] | "abc*+" |

**Result:** `"abc*+"` represents `a + (b * c)`

## 6. Code Implementation

```cpp
class Solution {
public:
    string infixToPostfix(string& s) {
        stack<char> st;
        string result;
        
        for(char ch : s) {
            if(isOperand(ch)) {
                result += ch;
            }
            else if(ch == '(') {
                st.push(ch);
            }
            else if(ch == ')') {
                while(st.top() != '(') {
                    result += st.top();
                    st.pop();
                }
                st.pop(); // Remove '('
            }
            else { // Operator
                while(!st.empty() && st.top() != '(' && 
                      shouldPop(st.top(), ch)) {
                    result += st.top();
                    st.pop();
                }
                st.push(ch);
            }
        }
        
        while(!st.empty()) {
            result += st.top();
            st.pop();
        }
        return result;
    }
    
private:
    bool isOperand(char c) {
        return isalnum(c);
    }
    
    int precedence(char op) {
        if(op == '+' || op == '-') return 1;
        if(op == '*' || op == '/') return 2;
        if(op == '^') return 3;
        return 0;
    }
    
    bool shouldPop(char stackTop, char current) {
        int topPrec = precedence(stackTop);
        int currPrec = precedence(current);
        return (topPrec > currPrec) || 
               (topPrec == currPrec && current != '^');
    }
};
```

## 7. Common Pitfalls

### Critical Mistakes:
- **Forgetting parentheses barrier:** Missing `st.top() != '('` check
- **Wrong associativity:** Using `>=` for right-associative `^` operator
- **Type confusion:** Comparing char with int instead of precedence values
- **Missing cleanup:** Not popping remaining operators at end
- **Empty stack access:** Not checking `st.empty()` before `st.top()`

### Edge Cases:
- Single operand: Return as-is
- Nested parentheses: Handled automatically by stack
- Right associative `^`: Use `>` not `>=` for equal precedence

## 8. Summary and Tips

### Key Takeaways:
- **Stack holds operators temporarily** based on precedence rules
- **Operands go directly to output**, operators go through stack
- **Precedence:** `^` (3) > `*/` (2) > `+-` (1)
- **Associativity:** Left (most ops) vs Right (`^` only)

### Interview Tips:
- **Start with basic version** (no parentheses), then add features
- **Trace through examples** to demonstrate understanding
- **Mention time/space complexity** early in explanation
- **Handle edge cases** explicitly (empty input, single operand)
- **Explain shouldPop() logic** clearly - this is the core insight

### Common Variants:
- Infix to prefix conversion
- Expression evaluation using two stacks
- Building expression trees
- Handling unary operators

### Quick Recognition:
- Stack + precedence rules = Shunting-Yard pattern
- Expression parsing problems often use this approach
- Time: O(n), Space: O(n) for most stack-based parsing
