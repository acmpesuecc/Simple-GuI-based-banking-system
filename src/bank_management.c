#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "bank.h"

struct customer s[100];
char file[] = "../data/user_data.csv";
char file_enc[] = "../data/user_data_enc.csv";
int size = 0;

void getFile(){
    FILE* fp = fopen(file_enc, "r");
    int i=0;
    if (!fp){
        printf("File is empty or file does not exist.\n");
    } else {
        char buffer[256];
        int row = 0,column=0;
        while (fgets(buffer,256, fp)){
            column = 0;
            row++;
            if (row == 1)continue;
            char* value = strtok(buffer, ",");
            while (value){
                decrypt(value);
                strcpy(s[i].last_login,value);
                value = strtok(NULL, ",");
                decrypt(value);
                strcpy(s[i].userName,value);
                value = strtok(NULL, ",");
                decrypt(value);
                strcpy(s[i].password,value);
                value = strtok(NULL, ",");
                decrypt(value);
                strcpy(s[i].mob_no,value);
                value = strtok(NULL, ",");
                decrypt(value);
                strcpy(s[i].accNo,value);
                value = strtok(NULL, ",");
                decrypt(value);
                strcpy(s[i].IFSCcode,value);
                value = strtok(NULL, ",");
                decrypt(value);
                s[i].balance = strtof(value,NULL);
                value = strtok(NULL, ",");
                decrypt(value);
                strcpy(s[i].email,value);
                value = strtok(NULL, ",");
                decrypt(value);
                strcpy(s[i].upiId,value);
                value = strtok(NULL, ",");
                decrypt(value);
                s[i].upiPass = atoi(value);
                value = strtok(NULL, ",");
                i++;
            }
        }
        fclose(fp);
    }
    size=i;

}

void putFile(){
    FILE* fp = fopen(file_enc, "w");
    int i=0;
    fputs("Logout_time,Username,Password,MobNo,AccountID,IFSC,Balance,Email,UPI_ID,UPI_passcode\n",fp);
    while(i<size)
    {
        encrypt(s[i].last_login);
        fputs(s[i].last_login, fp);
        fputc(',',fp);
        encrypt(s[i].userName);
        fputs(s[i].userName,fp);
        fputc(',',fp);
        encrypt(s[i].password);
        fputs(s[i].password,fp);
        fputc(',',fp);
        encrypt(s[i].mob_no);
        fputs(s[i].mob_no, fp);
        fputc(',', fp);
        encrypt(s[i].accNo);
        fputs(s[i].accNo,fp);
        fputc(',',fp);
        encrypt(s[i].IFSCcode);
        fputs(s[i].IFSCcode,fp);
        fputc(',',fp);
        char text[40], text2[40];
        sprintf(text, "%d", s[i].balance);
        encrypt(text);
        fputs(text,fp);
        fputc(',',fp);
        encrypt(s[i].email);
        fputs(s[i].email,fp);
        fputc(',',fp);
        encrypt(s[i].upiId);
        fputs(s[i].upiId,fp);
        fputc(',',fp);
        sprintf(text2, "%d", s[i].upiPass);
        encrypt(text2);
        fputs(text2,fp);
        fputs("\n",fp);
        i++;
    }
    fclose(fp);
}

void modify_details(int user_index, char password[40], char number[11], char email[50]){
    if (strlen(number) != 0){
        strcpy(s[user_index].mob_no, number);
        char mob_no_t[15];
        strcpy(mob_no_t, s[user_index].mob_no);
        strcat(mob_no_t, "@pesu");
        strcpy(s[user_index].upiId, mob_no_t);
    }
    if (strlen(password)!=0){
        strcpy(s[user_index].password, password);
    }
    if (strlen(email)!=0){
        strcpy(s[user_index].email, email);
    }
}

int get_user_index(char user[]){
    for(int i=0;i<size;i++){
        if(!strcmp(s[i].userName,user))
            return i;
    }
    return 0;
}

void accGenerator(char *s){
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

int set_upi_pass(int user_index, char *pass){
    pass = atoi(pass);
    if(pass>=100000 && pass<=999999){
        s[user_index].upiPass = pass;
        return 1;
    } else {
        return 2;
    }
}

int deposit(int user_index, char *amount){
    amount = atoi(amount);
    s[user_index].balance += amount;
    return 0;
}

int withdraw(int user_index, char *amount){
    int amount1 = atoi(amount);
    s[user_index].balance = s[user_index].balance - amount1;
    return 0;
}

int neft_withdraw(int user_index, char *amount, char *acc_id){
    int amount1 = atoi(amount);
    int receiver = -1;
    for (int i = 0; i < size; i++){
        if (strcmp(s[i].accNo, acc_id) == '0' || strcmp(s[i].accNo, acc_id) == 0) {
            receiver = i;
        }
    }
    if (receiver == -1){
        return 1;
    }
    s[user_index].balance = s[user_index].balance - amount1;
    s[receiver].balance += amount1;
    return 0;
}
int upi_transfer(int user_index, char *pass, char *amount, char *upi_rec){
    int amount1 = atoi(amount);
    int pass1 = atoi(pass);
    if (s[user_index].upiPass == pass1){
        int receiver = -1;
        for (int i = 0; i < size; i++){
            if (strcmp(s[i].upiId, upi_rec) == '0' || strcmp(s[i].upiId, upi_rec) == 0) {
                receiver = i;
            }
        }
        if (receiver == -1)
            return 2;
        s[user_index].balance = s[user_index].balance - amount1;
        s[receiver].balance += amount1;
        return 1;
    } else {
        return 0;
    }
}

void signup(char username[40], char password[40], char number[11], char email[50]){
    size++;
    int i = size-1;
    char mob_no_t[15], buffer[100];
    strcpy(s[i].userName, username);
    strcpy(s[i].password, password);
    strcpy(s[i].mob_no, number);
    strcpy(s[i].email, email);
    strcpy(s[i].IFSCcode, "PESU0002001");
    strcpy(buffer, __TIME__);
    strcat(buffer, "-");
    strcat(buffer, __DATE__);
    strcpy(s[i].last_login, buffer);
    accGenerator(s[i].accNo);
    s[i].balance = 0;
    strcpy(mob_no_t, s[i].mob_no);
    strcat(mob_no_t, "@pesu");
    strcpy(s[i].upiId, mob_no_t);
    s[i].upiPass = 0;
}

int login_checker(char username[], char pass[]){
    for (int i = 0; i < size; i++){
        if (strcmp(s[i].userName, username) == '0' || strcmp(s[i].userName, username) == 0) {
            char p[50];
            strcpy(p, s[i].password);
            //decrypt(p);
            strcpy(pass, p);
            return 1;
        }
    }
    return 0;
}

int login(char username[50], char password[50]){
    char pass[50];
    if (!login_checker(username, pass))
        return 1;
    if (strcmp(pass, password) == '0' || strcmp(pass, password) == 0)
        return 0;
    else {
        return 2;
    }
}

int find_user(char username[]){
    for (int i = 0; i < size; i++){
        if (strcmp(s[i].userName, username) == '0' || strcmp(s[i].userName, username) == 0) {
            return 1;
        }
    }
    return 0;
}

int pass_check(int user_index, char pass[40]){
    char password[40];
    strcpy(password, s[user_index].password);
    if (strcmp(password, pass) == '0' || strcmp(password, pass) == 0)
        return 1;
    else
        return 0;
}

void logout_set_time(int user_index){
    char buffer[100];
    strcpy(buffer, __TIME__);
    strcat(buffer, "-");
    strcat(buffer, __DATE__);
    strcpy(s[user_index].last_login, buffer);
}