#include<stdio.h>
#include<string.h>
#include<stdlib.h>




int main(){
    printf("------Welcome to PES's bank simulator------- \n (1)Login \n (2)Sign up\nEnter 1 or 2 respectfully\n");
    int a;
    char username[32],password[12],repass[12],passcheck[12];
    FILE* user;    
    
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
        printf("\n---------Welcome to the login page--------\nEnter your username: ");
        scanf("%s",&username);        
        FILE* fp = fopen("user.csv", "r");
    
        if (!fp)
            printf("Can't open file\n");
    
        else 
        {
            char buffer[1024];
    
            int row = 0;
            int column = 0;
    
            while (fgets(buffer,1024, fp)) 
            {
                column = 0;
                row++;

                //avoid printing 1st row
                if (row == 1)
                    continue;
    
                // Splitting the data
                char* value = strtok(buffer, ", ");
    
                while (value) 
                {

                    if(!strcmp(value,username))
                    {
                        value = strtok(NULL, ", ");
                        column++;
                        strcpy(passcheck,value);
                        break;
                    }
                    value = strtok(NULL, ", ");
                    
                }
               
            }
    
            // Close the file
            fclose(fp);

            printf("Enter your password: ");
            scanf("%s",&password);
            char pass1[12];
            for(int i=0;i<strlen(passcheck)-1;i++)pass1[i]=passcheck[i];
            if(strcmp(password,pass1)==0)printf("succesfull");
            else printf("invalid");
        
    }
    }
    else
    {
        printf("\n---------Welcome to the Sign up page--------\nEnter your username:");
        scanf("%s",&username);
        //function to check if the username is already taken
        while(1){
        printf("Enter your password:");
        scanf("%s",&password);
        //password should be greater than 8 digits for security
        printf("Renter your password:");
        scanf("%s",&repass);
        if(strcmp(repass,password)==0)
        {
            printf("signed up successfully");
            user = fopen("user.csv", "a+") ;
            fputs(",", user);
            fputs(username, user) ;
            fputs(",", user);
            fputs(password, user) ;   
            fputs("\n", user) ;
            fclose(user);
            break;
        }
        else{
            printf("try again by rentering the same password without spaces\n");
        }
        }

    }
    return 0;
}
