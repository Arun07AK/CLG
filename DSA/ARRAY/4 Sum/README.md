🎯 Pattern Recognition Triggers
When to Use This Pattern:
✅ TRIGGER PHRASES:
- "Find FOUR elements that sum to target"
- "Return all quadruplets that sum to X"
- "Four numbers with given sum"
- "All unique 4-element combinations"
- "No duplicate quadruplets allowed"
- "Sum of exactly 4 elements equals target"

✅ PROBLEM STRUCTURE:
- Need exactly 4 elements from array
- Sum condition: a + b + c + d = target
- Return all valid combinations (not just count)
- Duplicate quadruplets forbidden in result
- Can use same value in multiple quadruplets (different indices)
- Array can be modified (sorting allowed)
🔍 Pattern Recognition Checklist
□ Need to find exactly FOUR elements?
□ Elements must satisfy sum condition?
□ Return all valid combinations (not just existence)?
□ Duplicate combinations should be avoided?
□ Brute force O(n⁴) too slow for constraints?
□ Array size reasonable for O(n³) solution?

If ✅ → Use Sort + Fix Two + Two Pointers Pattern!
📝 Core Mathematical Insights
Key Strategy - Pattern Extension:
2Sum: Two pointers on sorted array           → O(n)
3Sum: Fix one element + 2Sum                 → O(n²) 
4Sum: Fix two elements + 2Sum                → O(n³)
kSum: Fix (k-2) elements + 2Sum              → O(n^(k-1))

Transform: "Find 4 elements" → "For each pair, find 2 elements"
Nested Problem Reduction:
4Sum Problem: a + b + c + d = target
↓
Fix a, b: Find c + d = target - a - b
↓ 
Two Pointers on remaining subarray

Result: O(n⁴) brute force → O(n³) optimized solution
🚨 Critical Implementation Details
Four-Level Duplicate Handling:
cpp// Level 1: Skip duplicate first fixed element (i)
if(i > 0 && nums[i] == nums[i-1]) continue;

// Level 2: Skip duplicate second fixed element (j)  
if(j > i+1 && nums[j] == nums[j-1]) continue;

// Level 3: Skip duplicate left values
while(left < right && nums[left] == nums[left-1]) left++;

// Level 4: Skip duplicate right values
while(left < right && nums[right] == nums[right+1]) right--;
Nested Loop Boundaries:
cppfor(int i = 0; i < n-3; i++)      // Need room for j, left, right
for(int j = i+1; j < n-2; j++)    // Need room for left, right
int left = j+1;                   // Start after second fixed element
int right = n-1;                  // Start at end
Target Calculation:
cpp// Avoid variable name conflict with function parameter
int twoSum = target - nums[i] - nums[j];
// Find: nums[left] + nums[right] = twoSum
📝 Optimized Implementation Template
cppclass Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        int n = nums.size();
        vector<vector<int>> result;
        
        // Step 1: Sort array for two pointers technique
        sort(nums.begin(), nums.end());
        
        // Step 2: Fix first element
        for(int i = 0; i < n-3; i++) {
            // Skip duplicate first elements
            if(i > 0 && nums[i] == nums[i-1]) continue;
            
            // Step 3: Fix second element  
            for(int j = i+1; j < n-2; j++) {
                // Skip duplicate second elements
                if(j > i+1 && nums[j] == nums[j-1]) continue;
                
                // Step 4: Two pointers for remaining elements
                int left = j + 1;
                int right = n - 1;
                long long twoSum = (long long)target - nums[i] - nums[j];
                
                while(left < right) {
                    long long sum = nums[left] + nums[right];
                    
                    if(sum == twoSum) {
                        // Found valid quadruplet
                        result.push_back({nums[i], nums[j], nums[left], nums[right]});
                        
                        // Move both pointers
                        left++;
                        right--;
                        
                        // Skip duplicates for both pointers
                        while(left < right && nums[left] == nums[left-1]) left++;
                        while(left < right && nums[right] == nums[right+1]) right--;
                    }
                    else if(sum < twoSum) {
                        left++;   // Need larger sum
                    }
                    else {
                        right--;  // Need smaller sum
                    }
                }
            }
        }
        
        return result;
    }
};
⚡ Key Optimization Techniques
1. Early Termination Optimizations:
cpp// Skip if smallest possible sum too large
if(nums[i] + nums[i+1] + nums[i+2] + nums[i+3] > target) break;

// Skip if largest possible sum too small  
if(nums[i] + nums[n-3] + nums[n-2] + nums[n-1] < target) continue;

// Similar optimizations for j loop
if(nums[i] + nums[j] + nums[j+1] + nums[j+2] > target) break;
if(nums[i] + nums[j] + nums[n-2] + nums[n-1] < target) continue;
2. Overflow Prevention:
cpp// Use long long for intermediate calculations
long long twoSum = (long long)target - nums[i] - nums[j];
long long sum = (long long)nums[left] + nums[right];
3. Efficient Duplicate Skipping:
cpp// Skip all duplicates in outer loops immediately
while(i < n-1 && nums[i] == nums[i+1]) i++;
while(j < n-1 && nums[j] == nums[j+1]) j++;
⚡ Complexity Analysis
Time Complexity:
✅ OPTIMIZED APPROACH:
Overall: O(n³)
- Sorting: O(n log n)
- Outer loop (i): O(n)  
- Inner loop (j): O(n)
- Two pointers: O(n) per (i,j) pair
- Total: O(n log n) + O(n³) = O(n³)

❌ BRUTE FORCE:
Time: O(n⁴) - four nested loops
Space: O(1) - no extra data structures
Space Complexity:
✅ SPACE ANALYSIS:
- Sorting: O(1) if in-place, O(n) if creating new array
- Result storage: O(k) where k = number of valid quadruplets
- Additional variables: O(1)
- Total: O(1) auxiliary space (not counting output)
🧩 Problem Variations
Type 1: 4Sum = Target (General)
cpp// Find all quadruplets that sum to specific target
vector<vector<int>> fourSum(vector<int>& nums, int target)
Type 2: 4Sum = 0 (Special Case)
cpp// Find all quadruplets that sum to zero
vector<vector<int>> fourSum(vector<int>& nums)
// target = 0, but logic remains same
Type 3: 4Sum Closest
cpp// Find quadruplet with sum closest to target  
int fourSumClosest(vector<int>& nums, int target)
// Track minimum difference instead of exact match
Type 4: 4Sum Count
cpp// Count number of valid quadruplets
int fourSumCount(vector<int>& nums, int target)
// Increment counter instead of storing quadruplets
🎯 Decision Tree
Need exactly 4 elements with sum condition?
├─ YES: Continue evaluation
└─ NO: Use different pattern (3Sum, kSum, etc.)

Array size manageable for O(n³) (< 1000 elements)?
├─ YES: 4Sum pattern applicable
└─ NO: Consider approximation or different approach

All quadruplets needed or just existence?
├─ All quadruplets: Return vector<vector<int>>
└─ Existence: Return bool, exit early on first match

Target value range large (overflow risk)?
├─ YES: Use long long for calculations
└─ NO: Standard int operations sufficient

Memory constraints?
├─ Tight: Optimize space, consider counting only
└─ Normal: Standard implementation with result storage
🔥 Similar Problems Using Same Pattern

3Sum - Simpler version: Fix one element + Two pointers
kSum (General) - Extend pattern: Fix (k-2) elements + Two pointers
Two Sum - Base case: Direct two pointers on sorted array
4Sum II - Different approach: Hash map for pairs + iterate
Count Quadruplets with Sum - Count instead of collect results
Closest 4Sum - Minimize difference instead of exact match
4Sum with Duplicates - Modified duplicate handling rules

💡 Key Mental Models
Pattern Scaling Strategy:
Think: "N-Sum = Fix (N-2) elements + 2Sum"
2Sum: Direct two pointers
3Sum: Fix 1 + 2Sum  
4Sum: Fix 2 + 2Sum
5Sum: Fix 3 + 2Sum
kSum: Fix (k-2) + 2Sum
Nested Duplicate Prevention:
Think: "Duplicates can come from N sources"
For 4Sum: 4 potential sources (i, j, left, right)
Each level needs independent duplicate handling
Skip at each level to prevent result duplicates
Boundary Management:
Each nested loop needs progressively tighter bounds:
i: [0, n-3]     → Need room for j, left, right
j: [i+1, n-2]   → Need room for left, right  
left: j+1       → Start after j
right: n-1      → Standard two pointers end
🚨 Common Pitfalls
1. Variable Name Conflicts
cpp// ❌ WRONG: Function parameter conflict
vector<vector<int>> fourSum(vector<int>& nums, int target) {
    int target = target - nums[i] - nums[j];  // Shadows parameter!
}

// ✅ CORRECT: Use different variable name
int twoSum = target - nums[i] - nums[j];
2. Incorrect Duplicate Boundary Conditions
cpp// ❌ WRONG: Wrong starting condition for j duplicates
if(j > i && nums[j] == nums[j-1]) continue;

// ✅ CORRECT: Skip duplicates after first occurrence
if(j > i+1 && nums[j] == nums[j-1]) continue;
3. Wrong Loop Boundaries
cpp// ❌ WRONG: Not leaving room for remaining elements
for(int i = 0; i < n; i++)    // May not have room for j, left, right
for(int j = i+1; j < n; j++)  // May not have room for left, right

// ✅ CORRECT: Account for remaining elements needed
for(int i = 0; i < n-3; i++)   // Leave room for j, left, right
for(int j = i+1; j < n-2; j++) // Leave room for left, right
4. Integer Overflow Issues
cpp// ❌ WRONG: Potential overflow with large targets
int twoSum = target - nums[i] - nums[j];  // May overflow!

// ✅ CORRECT: Use long long for safety
long long twoSum = (long long)target - nums[i] - nums[j];
5. Duplicate Skipping Direction Errors
cpp// ❌ WRONG: Looking in wrong direction
while(left < right && nums[left] == nums[left+1]) left++;   // Wrong direction
while(left < right && nums[right] == nums[right-1]) right--; // Wrong direction

// ✅ CORRECT: Compare with previously processed values
while(left < right && nums[left] == nums[left-1]) left++;   // Previous left
while(left < right && nums[right] == nums[right+1]) right--; // Previous right
🎯 Debugging Checklist
When 4Sum solution fails:
□ Array sorted before processing?
□ All four duplicate handling levels implemented?
□ Loop boundaries correct (n-3, n-2)?
□ Variable name conflicts avoided (target vs twoSum)?
□ Duplicate check conditions correct (j > i+1)?
□ Bounds checking in duplicate skipping (left < right first)?
□ Pointers moved after finding match (left++, right--)?
□ Integer overflow handled for large targets?
□ Duplicate skipping direction correct (compare with previous)?
□ Two pointers initialized correctly (left = j+1, right = n-1)?
🧪 General N-Sum Extension
cpp// Pattern extends to any N-Sum problem:
vector<vector<int>> kSum(vector<int>& nums, int target, int k) {
    sort(nums.begin(), nums.end());
    return kSumHelper(nums, target, k, 0);
}

vector<vector<int>> kSumHelper(vector<int>& nums, long long target, int k, int start) {
    vector<vector<int>> result;
    
    // Base case: 2Sum with two pointers
    if(k == 2) {
        int left = start, right = nums.size() - 1;
        while(left < right) {
            long long sum = nums[left] + nums[right];
            if(sum == target) {
                result.push_back({nums[left], nums[right]});
                // Skip duplicates
                while(left < right && nums[left] == nums[left+1]) left++;
                while(left < right && nums[right] == nums[right-1]) right--;
                left++; right--;
            }
            else if(sum < target) left++;
            else right--;
        }
        return result;
    }
    
    // Recursive case: Fix one element + (k-1)Sum
    for(int i = start; i < nums.size() - k + 1; i++) {
        // Skip duplicates
        if(i > start && nums[i] == nums[i-1]) continue;
        
        auto subResults = kSumHelper(nums, target - nums[i], k - 1, i + 1);
        for(auto& subResult : subResults) {
            result.push_back({nums[i]});
            result.back().insert(result.back().end(), subResult.begin(), subResult.end());
        }
    }
    
    return result;
}

🎯 Action Items

 Master the nested loop + two pointers pattern structure
 Practice all four levels of duplicate handling systematically
 Understand boundary calculations for nested loops
 Template the variable naming to avoid conflicts
 Recognize pattern extension to general kSum problems
 Handle integer overflow for large target values
 Debug systematically using the four-level checklist
