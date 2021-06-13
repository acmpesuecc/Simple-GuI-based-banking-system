#include<stdio.h>
#include<string.h>
#include<stdlib.h>




int main(){
    printf("------Welcome to PES's bank simulator------- \n (1)Login \n (2)Sign up\nEnter 1 or 2 respectfully\n");
    int a;
    char username[32],password[12],repass[12];
    FILE* user;
    FILE* pass;
    
    
    while(1)
    {
    scanf("%d",&a);
    if(a==1)
    {
        printf("You will be directed to the login page");
        break;
    }
    else if(a==2)
    {
        printf("You will be directed to the sign up page");
        break;
    }
    else
    {
        printf("Enter your choice again as a 1 or 2\n");
    }
    }
    if(a==1)
    {
        printf("\n---------Welcome to the login page--------\nEnter your username:");
        scanf("%s",&username);
        //function to assign searched username's password to variable comes here
        printf("Enter your password:");
        //password compared
        scanf("%s",&password);
        //password should be greater than 8 digits for security

    }
    else
    {
        printf("\n---------Welcome to the Sign up page--------\nEnter your username:");
        scanf("%s",&username);
        //function to check if the username is already taken
        printf("Enter your password:");
        scanf("%s",&password);
        printf("Renter your password:");
        scanf("%s",&repass);
        if(strcmp(repass,password)==0)
        {
            printf("signed up successfully");
            user = fopen("user.csv", "w") ;
            pass = fopen("pass.csv", "w") ;
            fputs(username, user) ;
            fputs("\n", user);
            fputs(password, pass) ;   
            fputs("\n", pass) ;
            fclose(pass) ;
            fclose(user);
        }
        else{
            printf("try again");
        }

    }
    return 0;
}