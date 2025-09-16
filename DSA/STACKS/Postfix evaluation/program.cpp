class Solution {
  public:
    int result(string s,int x,int y)
    {
        if(s=="+")
        {
            return x+y;
        }
        else if(s=="-")
        {
            return x-y;
        }
        else if(s=="*")
        {
            return x*y;
        }
        else if(s=="/")
        {
            return floor((double)x / y);
        }
        else if(s=="^")
        {
            return pow(x,y);
        }
        else {
            return -1;
        }
    }
    int evaluatePostfix(vector<string>& arr) {
        // code here
        stack<int> st;
        for(int i=0;i<arr.size();i++)
        {
            if(arr[i]=="+"||arr[i]=="-"||arr[i]=="*"||arr[i]=="/"||arr[i]=="^")
            {
                int a=st.top();
                st.pop();
                int b=st.top();
                st.pop();
                int result_store =result(arr[i],b,a);
                st.push(result_store);
            }

            else{
                st.push(stoi(arr[i]));
            }
        }
        int final=st.top();
        return final;
        
    }
};
