#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

int size=0;
char custom[]="";
char A[]="LOREM";
char B[]="IPSUM";
char C[]="CONSE";
char D[]="CRITO";

struct customer {
    char userName[40];
    char password[40];
    char accNo[40];//16bits long
    char IFSCcode[40];//10bits long
    float balance;
    char upiId[40];//10bits long
    int upiPass;//6digits
}s[100];

void encrypt(char *a)
{
    char n[40];
    int l=strlen(a);
    int count=0;
    for(int i=0;i<l;i++)
    {
        if(i%4==0)
        {n[i]=(a[i]+A[count]);}
        else if(i%3==0)
        {n[i]=(a[i]+C[count]);}
        else if(i%2==0)
        {n[i]=(a[i]+B[count]);}
        else
        {n[i]=(a[i]+D[count]);}
        count++;
        if(count==5)
        count=0;
    }
    n[l]=';'-2*l;
    count=0;
    for(int i=l+1;i<39;i++)
    {
        if(i%4==0)
        {n[i]=(B[count]+A[count]);}
        else if(i%3==0)
        {n[i]=(B[count]+C[count]);}
        else if(i%2==0)
        {n[i]=(D[count]+A[count]);}
        else
        {n[i]=(B[count]+D[count]);}
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

void decrypt(char *a)
{
    int l;
    for(int i=0;i<40;i++)
    {
        if((a[i]+2*i)==';')
        {l=i;
        break;}
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
        {n[i]=(a[i]-A[count]);}
        else if(i%3==0)
        {n[i]=(a[i]-C[count]);}
        else if(i%2==0)
        {n[i]=(a[i]-B[count]);}
        else
        {n[i]=(a[i]-D[count]);}
        count++;
        if(count==5)
        count=0;
    }
    n[l]='\0';
    strcpy(a,n);
}

void getFile(struct customer c[])
{
    FILE* fp = fopen("exceptional.csv", "r");
    int i=0;
    if (!fp)
        printf("File is empty!!\n");
    else 
    {
        char buffer[256];
        int row = 0,column=0;
        while (fgets(buffer,256, fp)) 
        {
            column = 0;
            row++;
            if (row == 1)continue;
  
            char* value = strtok(buffer, ",");
  
            while (value) 
            {
                strcpy(s[i].userName,value);
                value = strtok(NULL, ",");
                strcpy(s[i].password,value);
                value = strtok(NULL, ",");
                strcpy(s[i].accNo,value);
                value = strtok(NULL, ",");
                strcpy(s[i].IFSCcode,value);
                value = strtok(NULL, ",");
                s[i].balance = strtof(value,NULL);
                value = strtok(NULL, ",");
                strcpy(s[i].upiId,value);
                value = strtok(NULL, ",");
                s[i].upiPass = atoi(value);
                value = strtok(NULL, ",");
                i++;
            }
        }
        fclose(fp);
    }
    size=i;
}

void putFile(struct customer c[])
{
    FILE* fp = fopen("exceptional.csv", "w");
    int i=0;
    fputs("Username,Password,Accno,IFSCcode,Balance,UPIid,UPIpass\n",fp);
    while(i<size)
    {
        fputs(s[i].userName,fp);
        fputc(',',fp);
        fputs(s[i].password,fp);
        fputc(',',fp);
        fputs(s[i].accNo,fp);
        fputc(',',fp);
        fputs(s[i].IFSCcode,fp);
        fputc(',',fp);
        char text[20];
        sprintf(text, "%.2f", s[i].balance); 
        fputs(text,fp);
        fputc(',',fp);
        fputs(s[i].upiId,fp);
        fputc(',',fp);
        sprintf(text, "%d", s[i].upiPass); 
        fputs(text,fp);
        fputs("\n",fp);
        i++;
    }
    fclose(fp);
}

void IFSCGenerator(char *s)
{
    srand(time(0));
    char str[15]="PESU";
    for(int i=4;i<10;i++)
    {
        int n = rand()%10;
        char ch = '0'+n;
        str[i]=ch;
    }
    strcpy(s,str);
}

void accGenerator(char *s)
{
    srand(time(0));
    char str[17]="";
    for(int i=0;i<16;i++)
    {
        int n = rand()%10;
        char ch = '0'+n;
        str[i]=ch;
    }
    strcpy(s,str);
}

int check_user(char user[])
{
    for(int i=0;i<size;i++)
        if(!strcmp(s[i].userName,user))return 1;
    return 0;
}

void createUPI(int i)
{
    char str[40];
    printf("The upcoming information will be collected to create UPI: \n");
    printf("Enter your 10 digit mobile number: ");
    scanf("%s",&str);
    str[10]='@';
    str[11]='p';
    str[12]='e';
    str[13]='s';
    
    strcpy(s[i].upiId,str);
    pin_start:
    printf("Enter a 6 digit UPI PIN(avoid using 0 as 1st digit): ");
    scanf("%d",&s[i].upiPass);
    if(s[i].upiPass>=100000 && s[i].upiPass<=999999)
    {
        printf("Your UPI id was created successfully!\n");
        return;
    }
    else goto pin_start;
}

void deposit(char *user)
{
    float cash;
    printf("\nEnter the cash to be deposited: ");
    scanf("%f",&cash);
    getFile(s);
    for(int i=0;i<size;i++)
    {
        if(strcmp(s[i].userName,user)=='0'||strcmp(s[i].userName,user)==0)
        {s[i].balance+=cash;}
    }
    putFile(s);
    printf("Deposit successfull\n");
}

void withdraw(char *user)
{
    float cash;
    printf("\nEnter the cash to be withdrawn: ");
    scanf("%f",&cash);
    getFile(s);
    for(int i=0;i<size;i++)
    {
        if(strcmp(s[i].userName,user)=='0'||strcmp(s[i].userName,user)==0)
        {s[i].balance-=cash;}
    }
    putFile(s);
    printf("Withdraw successfull\n");
}

void balance(char *user)
{
    getFile(s);
    for(int i=0;i<size;i++)
        if(strcmp(s[i].userName,user)=='0'||strcmp(s[i].userName,user)==0)
            printf("Your Balance = %.2f\n",s[i].balance);
    putFile(s);
}

void transfer(char *user)
{
    char reciever[15],reci[15];
    int i,checkpass,u,flag=0;
    printf("\nEnter your UPIpass to continue: ");
    abc:
    scanf("%d",&checkpass);
    getFile(s);
    for(i=0;i<size;i++)
    {
        if(strcmp(s[i].userName,user)=='0'||strcmp(s[i].userName,user)==0)
        {   
            if(s[i].upiPass==checkpass)
            {
                printf("UPIpass matched\n");
                u=i;
            }
            else
            {
                printf("Wrong UPIpass,try again\n");
                goto abc;
            }
        }
    }
    printf("Enter a reciever UPIid\n");
    xyz:
    scanf("%s",&reciever);
    getFile(s);
    float cash;
    for(int i=0;i<size;i++)
    {
        if(strcmp(s[i].upiId,reciever)=='0'||strcmp(s[i].upiId,reciever)==0)
        {
            printf("Enter the amount of cash to be transferred: ");
            scanf("%f",&cash);
            s[u].balance-=cash;
            s[i].balance+=cash;
            flag=1;
            putFile(s);}
    }
    if(flag!=1)
    {
        printf("Enter the correct reciever upiID! ");
        goto xyz;
    }
    printf("Money transfer successfull!\n");
}

void quit()
{
    printf("Thanks for visiting");
}

void signup()
{
    size++;
    int i=size-1;
    char username[32],password[50],repass[50];
    user_start:
    printf("\n---------Welcome to the Sign up page--------\nEnter your username: ");
    scanf("%s",&username);
    if(check_user(username))
    {
        printf("Username has already been taken!\n");
        goto user_start;
    }
    pass_start:
    printf("Enter your password: ");
    scanf("%s",&password);
    if(strlen(password)<8)
    {
        printf("Enter a password greater than 8 characters!\n");
        goto pass_start;
    }
    printf("Renter your password: ");
    scanf("%s",&repass);
    if(strcmp(repass,password)==0)
    {
        strcpy(s[i].userName,username);
        
        strcpy(s[i].password,password);
        accGenerator(s[i].accNo);
        
        IFSCGenerator(s[i].IFSCcode);
        
        s[i].balance=0;
        createUPI(i);
        putFile(s);
        printf("You have successfully created a new account!\n");
    }
    else
    {
        printf("Re-entered password doesn't work, please try again!\n");
        goto pass_start;
    }
}

int login_checker(char username[],char pass[])
{
    getFile(s);
    for(int i=0;i<size;i++)
    {
        if(strcmp(s[i].userName,username)=='0'||strcmp(s[i].userName,username)==0){
            printf("Username found...\nPlease enter password\n");
            char p[50];
            strcpy(p,s[i].password);
            //decrypt(p);
            strcpy(pass,p);
            return 1;
        }
    }
    return 0;
}

void login()
{
    int y;
    char logcheckuser[50],logcheckpass[50],pass[50];
    printf("\n---------Welcome to the login page--------\n");
    user_start:
    printf("Enter your username: ");
    scanf("%s",&logcheckuser);
    if(!login_checker(logcheckuser,pass))
    {
        printf("Enter valid username!\n");
        goto user_start;
    }
    pass_start:
    printf("Enter your password: ");
    scanf("%s",&logcheckpass);
    if(strcmp(pass,logcheckpass)=='0'||strcmp(pass,logcheckpass)==0)
        printf("logged in\n");
    else{
        printf("enter again\n");
        goto pass_start;
    }
    whtodo:
    printf("\n----Select any of the following operations----\n");
    printf("(1)Deposit Money\n");
    printf("(2)Withdraw Money\n");
    printf("(3)Show Balance\n");
    printf("(4)Tranfer funda via UPI\n");
    printf("(5)Exit\n");
    printf("Enter an option: ");
    scanf("%d",&y);
    if(y==1){
        deposit(logcheckuser);
        goto whtodo;}
    else if(y==2){withdraw(logcheckuser);
        goto whtodo;}
    else if(y==3){balance(logcheckuser);
        goto whtodo;}
    else if(y==4){transfer(logcheckuser);
    goto whtodo;}
    else if(y==5)quit();
    else
    {
        printf("Enter one of the given values\n");
        goto whtodo;
    }
}

int main()
{
    printf("------Welcome to PES's bank simulator------- \n (1)Login \n (2)Sign up\nEnter 1 or 2 respectfully: ");
    int a;
    getFile(s);
    while(1)
    {
        scanf("%d",&a);
        if(a==1)
        {
            printf("You will be directed to the login page.....\n");
            login();
            break;
        }
        else if(a==2)
        {
            printf("You will be directed to the sign up page.....\n");
            signup();
            login();
            break;
        }
        else
            printf("Enter your choice again as a 1 or 2\n");
    }
    return 0;
}
