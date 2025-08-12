class Solution {
public:
    int pascalTriangleI(int r, int c) {
        return nCr(r-1,c-1);

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
