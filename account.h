

#ifndef ACCOUNT_H_
#define ACCOUNT_H_

#define MAX_NAME_LEN 30
#define MAX_COUNTRY_LEN 30
#define MAX_USERNAME_LEN 10
#define MAX_PASSWORD_LEN 8


struct Person
{

    char fullname[MAX_NAME_LEN + 1];
    
    int birth_year;

    double household_income;

    char country[MAX_COUNTRY_LEN + 1];

};

struct UserLogin
{

    char username[MAX_USERNAME_LEN + 1];
    char password[MAX_PASSWORD_LEN + 1];

};

struct Account
{
    
    int id;

    char type;

    struct Person person;
    struct UserLogin login;

};


void getPerson(struct Person * person);

void getAccount(struct Account * account);

void getUserLogin(struct UserLogin * login);

void updateAccount(struct Account * account);

void updatePerson(struct Person * person);

void updateUserLogin(struct UserLogin * login);

int authenticate(const struct Account accounts[], int max_accounts);


#endif