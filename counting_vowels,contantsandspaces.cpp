# include<iostream>
using namespace std;
    
/*
This program analyzes a string to count vowels, consonants, and words. It uses three counters: 
vcount for vowels (a,e,i,o,u in both cases), ccount for consonants (all non-vowel letters), 
and wcount for words (starting at 1 for the first word). The key logic handles multiple 
consecutive spaces by only incrementing the word count when encountering the first space 
after a non-space character, ensuring accurate word counting regardless of spacing.
*/
int main()
{

	string str="  my  name  is   arun ak       and";
    int vcount=0,ccount=0,wcount=1;;
    for(int i=0;str[i]!='\0';i++)
    {
        if(str[i]=='A'||str[i]=='a'||str[i]=='E'||str[i]=='e'||str[i]=='I'||str[i]=='i'||str[i]=='O'||str[i]=='o'||str[i]=='U'||str[i]=='u')
        {
            vcount++;
        }
        else if(str[i]==' '&& i>0 && str[i-1]!=' ')
        {
           wcount++; 
        }
        else if(str[i]!=' ')
        {
            ccount++;
        }
    }
    cout<<"the no of vowels = "<<vcount<<endl;
    cout<<"the no of words = "<<wcount<<endl;
    cout<<"the no of consonants = "<<ccount<<endl;
}