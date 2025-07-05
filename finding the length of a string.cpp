#include<iostream>
using namespace std;
int main()
{
    //finding the length of a string 
    //there are 2 methods 
    //method 1:using for loop
    string name="Arun is a good boy";
    int count=0;
    for(int i=0;name[i]!='\0';i++)
    {
        count++;
    }
    cout<<"the lenghth of the string is = "<<count<<endl;

    //method 2:using iterator
    count=0;
    string::iterator it;
    for(it=name.begin();it!=name.end();it++)
    {
        count++;
    }
    cout<<"the lenghth of the string is = "<<count<<endl;
}