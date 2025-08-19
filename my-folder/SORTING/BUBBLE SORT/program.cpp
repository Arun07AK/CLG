class Solution {
public:
    vector<int> bubbleSort(vector<int>& nums) {
        int n=nums.size();
        int flag=0;
        for(int i=0;i<n-1;i++)
        {
            flag =0;
            for(int j=0;j<n-i-1;j++)
            {
                if(nums[j]>nums[j+1])
                {
                    swap(nums[j],nums[j+1]);
                    flag=1;
                }
            }
            if(flag==0)
            {
                break;
            }
        }
        return nums ;

    }
};
