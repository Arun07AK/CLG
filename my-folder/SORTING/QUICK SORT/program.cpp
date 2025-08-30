class Solution {
public:
    void quickSortHelper(vector<int>& nums,int low, int high)
    {
        if(low>=high)//base case
        {
            return;
        }
        int pivot = partition(nums,low,high);
        //recursive calls 
        quickSortHelper(nums,low,pivot-1);
        quickSortHelper(nums,pivot+1,high);
    }
    vector<int> quickSort(vector<int>& nums) {
        int n = nums.size();
        quickSortHelper(nums, 0 , n-1);
        return nums;
    }
    int partition(vector<int>& nums,int low, int high)
    {
        int pivot = nums [low];
        int left = low+1;
        int right = high;
        while(left<=right)
        {
            while(left<=right && nums[left] < pivot)
            {
                left++;
            }
            while(left<=right && nums[right]>=pivot)
            {
                right--;
            }
            if(left<=right)
            {
                swap(nums[left],nums[right]);
                left++;
                right--;
            }
        }
        swap(nums[low],nums[right]);
        return right;
    }

};
