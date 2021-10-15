#include<string.h>
#include<stdio.h>

char A[]="LOREM";
char B[]="IPSUM";
char C[]="CONSE";
char D[]="CRATO";

void encrypt(char *a)
{
   char n[40];
    int l=strlen(a);
    int count=0;
    for(int i=0;i<l;i++)
    {
        if(i%4==0)
        {
            n[i]=(a[i]+A[count]);
            
        }
        else if(i%3==0)
        {
            n[i]=(a[i]+C[count]);
            
        }
        else if(i%2==0)
        {
            n[i]=(a[i]+B[count]);
            
        }
        else
        {
            n[i]=(a[i]+D[count]);
            
        }
        count++;
        if(count==5)
        count=0;
    }
    n[l]=';'-2*l;
    count=0;
    for(int i=l+1;i<39;i++)
    {
        if(i%4==0)
        {
            n[i]=(B[count]+A[count]);
            
        }
        else if(i%3==0)
        {
            n[i]=(B[count]+C[count]);
            
        }
        else if(i%2==0)
        {
            n[i]=(D[count]+A[count]);
            
        }
        else
        {
            n[i]=(B[count]+D[count]);
            
        }
        if(n[i]=='\n')
        n[i]='!';
        else if(n[i]=='\t')
        n[i]='"';
        else if(n[i]==',')
        n[i]='#';
        else if(n[i]==' ')
        n[i]='$';
        count++;
        if(count==5)
        count=0;
    }
    n[39]='\0';
    strcpy(a,n);
}
}

void decrypt(char *a)
{
    int l;
    for(int i=0;i<40;i++)
    {
        if((a[i]+2*i)==';')
        {
            l=i;
            break;
        }
    }
    char n[l];
    int count=0;
    for(int i=0;i<l;i++)
    {
        if(a[i]=='!')
        a[i]='\n';
        else if(a[i]=='*')
        a[i]='\t';
        else if(a[i]=='#')
        a[i]=',';
        else if(n[i]=='$')
        n[i]=' ';
        if(i%4==0)
        {
            n[i]=(a[i]-A[count]);
            
        }
        else if(i%3==0)
        {
            n[i]=(a[i]-C[count]);
            
        }
        else if(i%2==0)
        {
            n[i]=(a[i]-B[count]);
            
        }
        else
        {
            n[i]=(a[i]-D[count]);
            
        }
        count++;
        if(count==5)
        count=0;
    }
    n[l]='\0';
    strcpy(a,n);
}
