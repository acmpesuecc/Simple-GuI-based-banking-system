//Use this to encrypt/decrypt stuff, i might update it later
#include<string.h>
#include<stdio.h>
void encrypt(char *a)
{
    int l=strlen(a);int i=0;
    while(*a!='\0')
    {
        if(i%2==0)
        *a+=2*(l/2-i);
        else
        *a+=3*(l/2-i);
        if(*a==',')
        *a='!';
        a++;i++;
    }
}
void decrypt(char *a)
{
    int l=strlen(a);int i=0;
    while(*a!='\0')
    {
        if(*a=='!')
        *a=',';
        if(i%2==0)
        *a-=2*(l/2-i);
        else
        *a-=3*(l/2-i);
        a++;i++;
    }
}
