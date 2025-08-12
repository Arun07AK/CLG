class Solution {
public:
    vector<int> pascalTriangleII(int r) {
        vector<int> ans;
        for(int i=1;i<=r;i++)
        {
            ans.push_back(nCr(r-1,i-1));
        }
        return ans;
        

    }
private:
    int nCr(int r,int c)
    {
        int s=1;
        int n=r;
        int d=1;
        for(int i=0;i<c;i++)
        {
            s=s*n/d;
            n--;
            d++;
        }
        return s;
    }

    
};
