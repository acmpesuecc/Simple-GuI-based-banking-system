struct customer {
    char userName[40];
    char password[40];
    char mob_no[40];
    char accNo[40];//16bits long
    char IFSCcode[40];//10bits long
    int balance;
    char email[40];
    char upiId[40];//10bits long
    int upiPass;//6digits
    char last_login[40];
};

//Bank Management Functions
void getFile();
void putFile();
int get_user_index(char user[]);
int find_user(char username[]);
void signup(char username[40], char password[40], char number[10], char email[100]);
int login(char username[50], char password[50]);
int deposit(int user_index, char *amount);
int withdraw(int user_index, char *amount);
int neft_withdraw(int user_index, char *amount, char *acc_id);
int upi_transfer(int user_index, char *pass, char *amount, char *upi_rec);
int pass_check(int user_index, char pass[40]);
int set_upi_pass(int user_index, char *pass);
void logout_set_time(int user_index);
void modify_details(int user_index, char password[40], char number[11], char email[50]);

//Encrypt Decrypt
void encrypt(char *a);
void decrypt(char *a);

//Greet Functions
int greet_main();

//Dashboard Functions
int dashboard_main(int index, int argc, char *argv[]);