# include<iostream>
using namespace std;
    
/*program to change the letter from uppercase to lower case
the difference in ascii code for uppercase and lower case letter=32
and the capital letters have ascii values in the range 65 to 90
*/
int main()
{

	string str="WELCoME";
    for(int i=0;str[i]!='\0';i++)
    {
        if(str[i]>=65 && str[i]<=90)
        {
            str[i]=str[i]+32;
        }
    }
    cout<<str;
}
