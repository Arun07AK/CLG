
class Solution {
public:
    vector<int> rearrangeArray(vector<int>& nums) {
       int index=0;
       int len=nums.size();
       vector<int> ans(len);
       int positive=0;
       int negative=1;
       for(int i=0;i<len;i++)
       {
            if(nums[i]>0)
            {
                ans[positive]=nums[i];
                positive=positive+2;
            }
            else if(nums[i]<0)
            {
                ans[negative]=nums[i];
                negative=negative+2;
            }
       }
        return ans;

    }
};
