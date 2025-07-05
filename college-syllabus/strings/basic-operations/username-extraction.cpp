#include<iostream>
//extracting username from mailid
using namespace std;
int main()
{

    string mail;
    cout<<"enter the mail id"<<endl;
    getline(cin,mail);
    string name="";
    //method 1
    for(int i=0;i<mail.length();i++)
    {
        if(mail[i]=='@')
            break;
        name=name+mail[i];
        
    }
    cout<<"the username is = "<<name<<endl;

    //method 2
    name=mail.substr(0,(int)mail.find('@'));
    cout<<"the username is = "<<name<<endl;


}
