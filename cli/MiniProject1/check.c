#include<stdio.h>
#include<string.h>
#include<stdlib.h>

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

int check_user(char user[])
{
    FILE* fp = fopen("user.csv", "r");
    if (!fp)printf("File Empty\n");
    else 
    {
        char buffer[1024];
        int row = 0,column=0;
        while (fgets(buffer,1024, fp)) 
        {
            column = 0;
            row++;
            if (row == 1)continue;
            char* value = strtok(buffer, ", ");
            while (value) 
            {
                if (column == 0&&strcmp(user,value)==0)return 1;
                else break;
                value = strtok(NULL, ", ");
                column++;
            }
            //printf("");
        }
        fclose(fp);
    }
    return 0;
}

void signup()
{
    char username[32],password[12],repass[12];
    int balance;
    user_start:
    printf("\n---------Welcome to the Sign up page--------\nEnter your username: ");
    scanf("%s",&username);
    if(check_user(username))
    {
        printf("Username has already been taken!");
        goto user_start;
    }
    pass_start:
    printf("Enter your password:");
    scanf("%s",&password);
    if(strlen(password)<8)
    {
        printf("Enter a password greater than 8 characters!\n");
        goto pass_start;
    }
    printf("Renter your password:");
    scanf("%s",&repass);
    if(strcmp(repass,password)==0)
    {
        FILE* fp = fopen("user.csv", "a+");
        if (!fp) printf("Can't open file\n");
        else
        {
            encrypt(password);
            // printf("Enter bank balance in rupees: ");
            // scanf("%d",&balance);
            fprintf(fp, "%s,%s\n", username, password);
            printf("\nNew Account added to record\n");
        }
        
        fclose(fp);
    }
    else
    {
        printf("Re-entered password doesn't work, please try again!");
        goto pass_start;
    }
}

int login_checker(char username[],char pass[])
{
    FILE* fp = fopen("user.csv", "r");
  
    if (!fp)
    {
        printf("File is empty!!\n");
        return 0;
    }
    else 
    {
        char buffer[1024];
        int row = 0,column=0;
  
        while (fgets(buffer,1024, fp)) 
        {
            column = 0;
            row++;
            if (row == 1)continue;
  
            char* value = strtok(buffer, ", ");
  
            while (value) 
            {
                if (column == 0 && strcmp(username,value)==0)
                {
                    value = strtok(NULL, ", ");
                    strcpy(pass,value);
                    return 1;
                }

                value = strtok(NULL, ", ");

            }
        }
        fclose(fp);
    }
    return 0;
}
void login()
{
    char pass[12],username[20],password[12];
    printf("\n---------Welcome to the login page--------\n");
    user_start:
    printf("Enter your username:");
    scanf("%s",&username);
    if(!login_checker(username,pass))
    {
        printf("Enter valid username!\n");
        goto user_start;
    }
    pass_start:
    printf("Enter your password:");
    scanf("%s",&password);
    decrypt(pass);
    for(int i=0;i<strlen(pass)-1;i++)
    {
        if(strlen(pass)-1!=strlen(password))
        {
            printf("Enter valid password!\n");
            goto pass_start;
        }
        if(password[i]!=pass[i])
        {
            printf("Enter valid password!\n");
            goto pass_start;
        }
    }
    printf("Login Successfull!!!!\n");
}
int main()
{
    printf("------Welcome to PES's bank simulator------- \n (1)Login \n (2)Sign up\nEnter 1 or 2 respectfully\n");
    int a;
    while(1)
    {
        scanf("%d",&a);
        if(a==1)
        {
            printf("You will be directed to the login page.....");
            break;
        }
        else if(a==2)
        {
            printf("You will be directed to the sign up page.....");
            break;
        }
        else
        {
            printf("Enter your choice again as a 1 or 2\n");
        }
    }
    if(a==1){
        login();}
    else {
        signup();
        login();}
    return 0;
}
