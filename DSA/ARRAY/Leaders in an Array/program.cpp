class Solution {
public:
    vector<int> leaders(vector<int>& nums) {
        
        int r=nums.size()-2;
        vector<int> ans;
        int maxSoFar=INT_MIN;
        ans.push_back(nums[nums.size()-1]);
        maxSoFar=nums[nums.size()-1];
        
        while(r>=0)
        {
            
            if(nums[r]>maxSoFar)
            {
                maxSoFar=nums[r];
                ans.push_back(nums[r]);
            }
            
            r--;
            
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};
