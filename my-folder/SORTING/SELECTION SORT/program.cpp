class Solution {
public:
    vector<int> selectionSort(vector<int>& nums) {
        int n=nums.size();
        int k;
        for(int i=0;i<n-1;i++)
        {
            k=i;
            for(int j=i+1;j<n;j++)
            {
                if(nums[j]<nums[k])
                {
                    k=j;
                }
            }
            swap(nums[i],nums[k]);
        }
        return nums;

    }
};
