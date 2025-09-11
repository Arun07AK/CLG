class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        int n=nums.size();
        sort(nums.begin(),nums.end());
        int left ;
        int right;
        int target;
        vector<int> temp;
        vector<vector<int>> ans;
        for(int i=0;i<n;i++)
        {
            if(i>0 && nums[i]==nums[i-1])
            {
                continue;
            }
            left =i+1;
            right =n-1;
            target=-nums[i];
            
            while(left<right)
            {
                if(nums[left]+nums[right]==target )
                {
                    temp.clear();
                    temp.push_back(nums[i]);
                    temp.push_back(nums[left]);
                    temp.push_back(nums[right]);
                    ans.push_back(temp);
                    left++;
                    right--;
                    while(nums[left]==nums[left-1] && left<right)
                    {
                        left++;
                    }
                    while(nums[right]==nums[right+1] && left<right)
                    {
                        right--;
                    }
                }
                else if(nums[left]+nums[right]<target)
                {
                    left++;
                }
                else
                {
                    right--;
                }
                
            }
            

        }
        return ans;
        
    }
};
