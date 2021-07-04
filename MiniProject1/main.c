#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void deposit(char *g)
{
    int n=1;
    float cash,depocash;
    printf("enter the amount of cash to be deposited\n");
    scanf("%f",&depocash);
    char user[20];
    strcpy(user,g);
    char token[1024];
    
    FILE* p = fopen("user.csv", "r");
    FILE* s=fopen("check.csv","w");
    if(!p)printf("File empty\n");
    if(!s)printf("File empty\n");
    else 
    {
        char buffer[1024];
        int row = 0,column=0;
        char cashstr[20],cashstr1[20];
        fputs("Username,password,balance\n",s);
        while (fgets(buffer,1024, p)) 
        {
            column = 0;
            row++;
            if (row == 1)continue;
            char* value = strtok(buffer, ",");
            if(!strcmp(user,value))
            {fputs(value,s);
            fputs(",",s);
            value = strtok(NULL, ",");
            fputs(value,s);
            fputs(",",s);
            value = strtok(NULL, ",");
            cash=atof(value);
            cash+=depocash;
            gcvt(cash,15,cashstr);
            for(int e=0;e<strlen(cashstr)-1;e++)
            {cashstr1[e]=cashstr[e];}
            fputs(cashstr1,s);
            fputs("\n",s);}
            else
            {fputs(value,s);
            fputs(",",s);
            value = strtok(NULL, ",");
            fputs(value,s);
            fputs(",",s);
            value = strtok(NULL, ",");
            fputs(value,s);
            }
        }
        fclose(p);
        fclose(s);
        FILE* p = fopen("user.csv", "w+");
        FILE* s=fopen("check.csv","r");
        while(fgets(buffer,1024,s))
        {fputs(buffer,p);}
        fclose(p);
        fclose(s);
        printf("tasks performed successfully");
    }
}

void withdraw(char *g)
{
    int n=1;
    float cash,withcash;
    printf("enter the amount of cash to be withdrawn\n");
    scanf("%f",&withcash);
    char user[20];
    strcpy(user,g);
    char token[1024];
    
    FILE* p = fopen("user.csv", "r");
    FILE* s=fopen("check.csv","w");
    if(!p)printf("File empty\n");
    if(!s)printf("File empty\n");
    else 
    {
        char buffer[1024];
        int row = 0,column=0;
        char cashstr[20],cashstr1[20];
        fputs("Username,password,balance\n",s);
        while (fgets(buffer,1024, p)) 
        {
            column = 0;
            row++;
            if (row == 1)continue;
            char* value = strtok(buffer, ",");
            if(!strcmp(user,value))
            {fputs(value,s);
            fputs(",",s);
            value = strtok(NULL, ",");
            fputs(value,s);
            fputs(",",s);
            value = strtok(NULL, ",");
            cash=atof(value);
            cash-=withcash;
            gcvt(cash,15,cashstr);
            for(int e=0;e<strlen(cashstr)-1;e++)
            {cashstr1[e]=cashstr[e];}
            fputs(cashstr1,s);
            fputs("\n",s);}
            else
            {fputs(value,s);
            fputs(",",s);
            value = strtok(NULL, ",");
            fputs(value,s);
            fputs(",",s);
            value = strtok(NULL, ",");
            fputs(value,s);
            }
        }
        fclose(p);
        fclose(s);
        FILE* p = fopen("user.csv", "w+");
        FILE* s=fopen("check.csv","r");
        while(fgets(buffer,1024,s))
        {fputs(buffer,p);}
        fclose(p);
        fclose(s);
        printf("tasks performed successfully");
    }
}

int balance(char *g)
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
  
            char* value = strtok(buffer, ",");
  
            while (value) 
            {
                if (column == 0 && strcmp(g,value)==0)
                {
                    value = strtok(NULL, ",");
                    value = strtok(NULL, ",");
                    printf("%s",value);
                    return 0;
                }
 
                value = strtok(NULL, ",");

            }
        }
        fclose(fp);
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
            if(!strcmp(user,value))
            return 1;
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
        if (!fp) 
        {
            printf("Can't open file\n");
        }
        else
        {
            printf("Enter bank balance in rupees: ");
            scanf("%d",&balance);
            fprintf(fp, "%s,%s,%d\n", username, password,balance);
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
  
            char* value = strtok(buffer, ",");
  
            while (value) 
            {
                if (column == 0 && strcmp(username,value)==0)
                {
                    value = strtok(NULL, ",");
                    strcpy(pass,value);
                    return 1;
                }
 
                value = strtok(NULL, ",");

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
   // printf("%s",pass);
    if(strcmp(pass,password)=='0')
    {
        printf("Enter valid password!\n");
        goto pass_start;
    }
    //printf("Login Successfull!!!!\n");
    int q;
    printf("logged in");
    printf("--redirect to bank--\ntype 1 or 2 or 3 for deposit or withdraw or to check balance respectfully\n");
    scanf("%d",&q);
    if(q==1)
    deposit(username);
    else if(q==2)
    withdraw(username);
    else if(q==3)
    balance(username);
    else
    printf("quit successfully");
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
            login();
            break;
        }
        else if(a==2)
        {
            printf("You will be directed to the sign up page.....");
            signup();
            break;
        }
        else
        {
            printf("Enter your choice again as a 1 or 2\n");
        }
    }
    return 0;
}
