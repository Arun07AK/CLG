class Solution {
  public:
    string infixToPostfix(string& s) {
        stack<char> st;
        string r;
        for(int i=0;s[i]!='\0';i++)
        {
            if(s[i]=='^')
            {
                while(!st.empty() && imp(st.top())>imp(s[i]) && (st.top()!='('))
                {
                    r+=st.top();
                    st.pop();
                }
                st.push(s[i]);
            }
            else if(s[i]=='+'||s[i]=='-'||s[i]=='*'||s[i]=='/')
            {
                while(!st.empty() && imp(st.top())>=imp(s[i]) && (st.top()!='('))
                {
                    r+=st.top();
                    st.pop();
                }
                st.push(s[i]);
            }
            else if(s[i]=='(')
            {
                st.push(s[i]);
            }
            else if(s[i]==')')
            {
                while(st.top()!='(')
                {
                    r+=st.top();
                    st.pop();
                }
                st.pop();
            }
            else{
                r+=s[i];
            }
        }
        while(!st.empty())
        {
            r+=st.top();
            st.pop();
        }
        return r;
        
    }
    int imp(char c)
    {
        if(c=='+'||c=='-')
        {
            return 1;
        }
        if(c=='*'||c=='/')
        {
            return 2;
        }
        if(c=='^')
        {
            return 3;
        }
        return 0;
    }
};
