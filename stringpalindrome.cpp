#include<iostream>
using namespace std;
/*
This program checks if a user-entered string is a palindrome (reads the same forwards and backwards).
It prompts the user to input a string using getline() to handle spaces, then creates a reversed 
copy by iterating through the original string from end to beginning and concatenating each character 
to a new string. Finally, it compares the original string with the reversed string using the 
compare() method to determine if they are identical and displays the appropriate result.
*/
int main()
{
    
    
    string str;
    cout<<"enter the string to be tested "<<endl;
    getline(cin,str);
    //method 1:string concatenation   
    string s="";
    for(int i=str.length()-1;i>=0;i--)
    {
        s=s+str[i];
    }
    if(str.compare(s)==0)
    {
        cout<<"it is palindrome";
    }
    else{
        cout<<"not a palindrome ";
    }
    
    //method 2:building string character by character using 2 pointer technique
    string rev="";
    int len=(int)str.length();
    rev.resize(len);
    for(int i=0 ,j=len-1;i<len;i++,j--)
    {
        rev[i]=str[j];
    }
    rev[len]='\0';
    if(str.compare(rev)==0)
    {
        cout<<"it is palindrome";
    }
    else{
        cout<<"not a palindrome ";
    }
    
}
