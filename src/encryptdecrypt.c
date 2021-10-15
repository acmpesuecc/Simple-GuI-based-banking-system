#include<string.h>
#include<stdio.h>

void encrypt(char *a)
{
    char A[]="LOREM";
    char B[]="IPSUM";
    char C[]="CONSE";
    char D[]="CRATO";
    char n[40];
    int l=strlen(a);
    int count=0;
    for(int i=0;i<2*l;i+=2)
    {
        if(i%4==0)
        {
            n[i]=(a[i/2]+A[count]);
            
        }
        else if(i%3==0)
        {
            n[i]=(a[i/2]+C[count]);
            
        }
        else if(i%2==0)
        {
            n[i]=(a[i/2]+B[count]);
            
        }
        else
        {
            n[i]=(a[i/2]+D[count]);
            
        }
        if(n[i]=='\n')
        n[i]='!';
        else if(n[i]=='\t')
        n[i]='*';
        else if(n[i]==',')
        n[i]='#';
        count++;
        if(count==5)
        count=0;
    }
    count=0;
    for(int i=1;i<39;i+=2)
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
    n[l]=';'-2*l;
    n[39]='\0';
    strcpy(a,n);
}

void decrypt(char *a)
{
    char A[]="LOREM";
    char B[]="IPSUM";
    char C[]="CONSE";
    char D[]="CRATO";
    int l;
    for(int i=0;i<40;i++)
    {
        if((a[i]+2*i)==';')
        {
            l=i/2;
            //printf("%d",l);
            break;
        }
    }
    char n[l];
    int count=0;
    for(int i=0;i<2*l;i+=2)
    {
        if(a[i]=='!')
        a[i]='\n';
        else if(a[i/2]=='*')
        a[i]='\t';
        else if(a[i/2]=='#')
        a[i]=',';
        else if(n[i/2]=='$')
        a[i]=' ';
        if((i/2)%4==0)
        {
            n[i/2]=(a[i]-A[count]);
            
        }
        else if((i/2)%3==0)
        {
            n[i/2]=(a[i]-C[count]);
            
        }
        else if((i/2)%2==0)
        {
            n[i/2]=(a[i]-B[count]);
            
        }
        else
        {
            n[i/2]=(a[i]-D[count]);
            
        }
        count++;
        if(count==5)
        count=0;
    }
    n[l]='\0';
    strcpy(a,n);
}
