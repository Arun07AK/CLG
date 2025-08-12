class Solution {
public:
    vector<vector<int>> pascalTriangleIII(int n) {
        vector<vector<int>> ans;
        vector <int> temp;
        int r=n;
        for(int i=1 ;i<=r;i++)
        {
            temp.clear();
            for(int j=1;j<=i;j++)
            {
                temp.push_back(nCr(i-1,j-1));
            }
            ans.push_back(temp);

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
