class Solution {
public:
void rotateMatrix(vector<vector<int>>& matrix){
        vector<vector<int>> ans;
        vector <int> temp;
        int n=matrix.size();
        for(int i=1 ;i<n;i++)
        {   
            for(int j=0;j<i;j++)
            {
                swap(matrix[j][i],matrix[i][j]);
            }
            
        }
        for(int i=0;i<n;i++)
        {
            reverse(matrix[i].begin(), matrix[i].end());
        }
              
    }

    
}; 
