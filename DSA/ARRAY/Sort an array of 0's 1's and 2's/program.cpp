#include<bits/stdc++.h>
using namespace std;


class Solution {
public:
    void sortZeroOneTwo(vector<int>& nums) {
        //only 0 , 1 , 2 
        //sort it in non dec order 
        //without making a copy 
        int n=nums.size();
        int low =0;
        int mid=0;
        int high=n-1;
        while(mid<=high)
        {
            if(nums[mid]<1)
            {
                swap(nums[low],nums[mid]);
                low++;
                mid++;
            }
            else if(nums[mid]>1)
            {
                swap(nums[high],nums[mid]);
                high--;
            }
            else if(nums[mid]==1)
            {
                mid++;
            }
        }
        
    }
};

int main() {
    vector<int> nums = {0, 2, 1, 2, 0, 1};
    
    // Create an instance of Solution class
    Solution sol;

    sol.sortZeroOneTwo(nums);
    
    // Print the array elements after sorting
    cout << "After sorting:" << endl;
    for (int i = 0; i < nums.size(); i++) {
        cout << nums[i] << " ";
    }
    cout << endl;
    
    return 0;
}
