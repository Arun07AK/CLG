class Solution {
public:
    vector<int> twoSum(vector<int> nums, int target) {
        
        int n=nums.size();
        
        vector<vector<int>> eleIndex;
        vector<int> ans;
        for(int i=0;i<n;i++)
        {
            eleIndex.push_back({nums[i],i});
        }
        int left=0;
        int right =eleIndex.size()-1;
        sort(eleIndex.begin(),eleIndex.end(),[](const vector<int>& a, const vector<int>& b)
        {
            return a[0]<b[0];
        });
        while(left<right)
        {
            if(eleIndex[left][0]+eleIndex[right][0]==target)
            {
                ans.push_back(eleIndex[left][1]);
                ans.push_back(eleIndex[right][1]);
                return ans;
            }
            else if(eleIndex[left][0]+eleIndex[right][0]<target)
            {
                left++;
            }
            else{
                right--;
            }
        }
        return{-1,-1};

              
    }

    
};
