class Solution {
public:
    vector<int> mergeSort(vector<int>& nums) {
        int n=nums.size();
        mergeSortHelper(nums,0,n-1);
        return nums;
    }
    void mergeSortHelper(vector<int>&nums,int low , int high)
    {
        if(low>=high)
        {
            return;
        }
        int mid=(low+high)/2;
        mergeSortHelper(nums,low,mid);
        mergeSortHelper(nums,mid+1,high);
        merge(nums,low,mid,high);
    }
    void merge(vector<int>&nums,int low ,int mid , int high)
    {
        int left;
        int right;
        left=low;
        right=mid+1;
        vector<int> b;
        while(left<=mid && right<=high)
        {
            if(nums[left]<=nums[right])
            {
                b.push_back(nums[left]);
                left++;
            }
            else if(nums[left]>nums[right])
            {
                b.push_back(nums[right]);
                right++;
            }
        }
        for(;left<=mid;left++)
        {
            b.push_back(nums[left]);
            
        }
        for(;right<=high;right++)
        {
            b.push_back(nums[right]);
        }
        for(int i=0;i<b.size();i++)
        {
            nums[low+i]=b[i];
        }


    }
};
