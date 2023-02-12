/*
    ==================================================
    Assignment #2 Milestone #2
    ==================================================
    Name   : Shayan Chabook
    ID     : 159844208
    Email  : Schabook@myseneca.ca
    Section: ZAA
*/

#define _CRT_SECURE_NO_WARNINGS

#include "account.h"
#include "accountTicketingUI.h"
#include "commonHelpers.h"
#include <stdio.h>
#include <string.h>

static int CurrentID = 50600;
 
void getAccount(struct Account *account)
{
    
    printf("New Account Data (Account#:%d)\n", CurrentID);
    printf("----------------------------------------\n");
    account->id = CurrentID;
    CurrentID++;

    printf("Enter the account type (A=Agent | C=Customer): ");

    account->type = getCharOption("AC");

    printf("\n");

    getPerson(&(account->person));

    if (account->type == 'A')
        getUserLogin(&(account->login));
    else 
    {
        account->login.username[0] = '\0';
        account->login.password[0] = '\0';
    }

    printf("*** New account added! ***\n\n");
}

void getPerson(struct Person *person)
{

    printf("Person Data Input\n");
    printf("----------------------------------------\n");
    printf("Enter the person's full name (30 chars max): ");

    getCString(person->fullname, 1, MAX_NAME_LEN);

    printf("Enter birth year (current age must be between 18 and 110): ");

    int Current_Year = thisYear();

    person->birth_year = getIntFromRange(Current_Year - 110, Current_Year - 18);

    printf("Enter the household Income: $");

    person->household_income = getPositiveDouble();

    printf("Enter the country (30 chars max.): ");

    getCString(person->country, 1, MAX_COUNTRY_LEN);

    makeUpper(person->country);

    printf("\n");
}

void getUserLogin(struct UserLogin *login)
{
    printf("User Login Data Input\n");
    printf("----------------------------------------\n");

    char TMP_UN[MAX_USERNAME_LEN + 1];
    do
    {
        printf("Enter user login (10 chars max): ");

        getCString(TMP_UN, 1, MAX_USERNAME_LEN);
    } 
    while (!checkUser(TMP_UN));

    strcpy(login->username, TMP_UN);

    char TMP_PSS[MAX_PASSWORD_LEN + 1] = {0};

    do
    {
        printf("Enter the password (must be 8 chars in length): ");

        getCString(TMP_PSS, MAX_PASSWORD_LEN, MAX_PASSWORD_LEN);

    } 
    while (!checkPass(TMP_PSS));

    strcpy(login->password, TMP_PSS);

    printf("\n");
}

void updateAccount(struct Account *account)
{
    while (1)
    {
        printf("Update Account: %d (%s)\n", account->id, account->person.fullname);

        printf("----------------------------------------\n");

        printf("1) Update account type (current value: %c)\n", account->type);

        printf("2) Person\n");

        printf("3) Login\n");

        printf("0) Done\n");

        printf("Selection: ");

        int Option = getIntFromRange(0, 3);

        printf("\n");

        if (Option == 1)
        {
            printf("Enter the account type (A=Agent | C=Customer): ");

            account->type = getCharOption("AC");

            printf("\n");

            if (account->type == 'A')
            {
                printf("Agent type accounts require a user login.  Please enter this information now:\n\n");

                getUserLogin(&(account->login));
            }
            else
            {
                account->login.username[0] = '\0';
                account->login.password[0] = '\0';
            }
        }
        else if (Option == 2)

            updatePerson(&(account->person));

        else if (Option == 3)

        {
            if (account->type == 'C')

                printf("ERROR:  Customer account types don't have user logins!\n\n");

            else

                updateUserLogin(&(account->login));
        }

        else

            return;
    }
}

void updatePerson(struct Person *person)
{
    while (1)
    {
        printf("Person Update Options\n");

        printf("----------------------------------------\n");

        printf("1) Full name (current value: %s)\n", person->fullname);

        printf("2) Household Income (current value: $%.2lf)\n", person->household_income);

        printf("3) Country (current value: %s)\n", person->country);

        printf("0) Done\n");

        printf("Selection: ");

        int Option = getIntFromRange(0, 3);

        printf("\n");

        if (Option == 1)
        {
            printf("Enter the person's full name (30 chars max): ");

            getCString(person->fullname, 1, MAX_NAME_LEN);

            printf("\n");
        }
        else if (Option == 2)
        {
            printf("Enter the household Income: $");

            person->household_income = getPositiveDouble();

            printf("\n");
        }
        else if (Option == 3)
        {
            printf("Enter the country (30 chars max.): ");

            getCString(person->country, 1, MAX_COUNTRY_LEN);

            makeUpper(person->country);

            printf("\n");
        }

        else

            return;
    }
}

void updateUserLogin(struct UserLogin *login)
{
    while (1)
    {
        printf("User Login: %s - Update Options\n", login->username);

        printf("----------------------------------------\n");

        printf("1) Password\n");

        printf("0) Done\n");

        printf("Selection: ");

        int Option = getIntFromRange(0, 1);

        printf("\n");

        if (Option == 1)
        {
            char TMP_PSS[MAX_PASSWORD_LEN + 1] = {0};
            do
            {
                printf("Enter the password (must be 8 chars in length): ");

                getCString(TMP_PSS, MAX_PASSWORD_LEN, MAX_PASSWORD_LEN);

            } 
            while (!checkPass(TMP_PSS));

            strcpy(login->password, TMP_PSS);

            printf("\n");
        }
        else

            return;
    }
}

int authenticate(const struct Account accounts[], int max_accounts)
{
    char UserName[25];
    char Password[25];

    int Remaining_Attemps = 3;

    while (Remaining_Attemps > 0)
    {
        int IDX = findAccountIndexByAcctNum(-1, accounts, max_accounts, 1);

        printf("User Login        : ");

        scanf("%100[^\n]", UserName);

        clearStandardInputBuffer();

        printf("Password          : ");

        scanf("%100[^\n]", Password);

        clearStandardInputBuffer();

        int Is_Autherized = (IDX != -1 &&
                             strcmp(accounts[IDX].login.username, UserName) == 0 &&
                             strcmp(accounts[IDX].login.password, Password) == 0)
                                ? 1
                                : 0;

        if (!Is_Autherized)
        {
            Remaining_Attemps--;
            printf("INVALID user login/password combination! [attempts remaining:%d]\n\n", Remaining_Attemps);
        }
        else
            return IDX;
    }
    return 0;
}
