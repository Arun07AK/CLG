vector<vector<int>> rotateMatrix(vector<vector<int>>& matrix) {
    vector<vector<int>> ans;    
    vector<int> temp;
    int n = matrix.size();
    
    for(int i = 0; i < n; i++) {
        temp.clear();
        for(int j = n-1; j >= 0; j--) {
            temp.push_back(matrix[j][i]);  
        }
        ans.push_back(temp);
    }
    return ans;
}
