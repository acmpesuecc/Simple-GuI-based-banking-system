//Use this to encrypt/decrypt stuff, i might update it later
#include<string.h>
void encrypt(char *a)
{
    int l=strlen(a);int i=0;
    while(*a!=0)
    {
        if(i%2==0)
        *a+=2*(l/2-i);
        else
        *a-=2*(l/2+i);
        a++;i++;
    }
}
void decrypt(char *a)
{
    int l=strlen(a);int i=0;
    while(*a!=0)
    {
        if(i%2==0)
        *a-=2*(l/2-i);
        else
        *a+=2*(l/2+i);
        a++;i++;
    }
}