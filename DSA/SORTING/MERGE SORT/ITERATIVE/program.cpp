
class Solution {
  public:
    void mergeSort(vector<int>& arr, int l, int r) {
        int n= arr.size();
        int size=1;
        for(;size<n;size*=2)
        {
            for(int left=0;left<n;left+=2*size)
            {
                int mid=min(left+size-1,n-1);
                int high=min(left+size*2-1,n-1);
                if(mid<high)
                {
                    merge(arr,left,mid,high);
                }
            }
        }
        
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
