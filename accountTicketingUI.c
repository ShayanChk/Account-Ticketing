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

#include "accountTicketingUI.h"
#include "account.h"
#include "commonHelpers.h"
#include <stdio.h>
#include <string.h>

void displayAccountDetailHeader(void){

    printf("Acct# Acct.Type Full Name       Birth Income      Country    Login      Password\n");
    printf("----- --------- --------------- ----- ----------- ---------- ---------- --------\n");
}

void displayTicketDetailHeader(void)
{
    printf("------ ----- --------------- ------ ------------------------------ --------\n");
    printf("Ticket Acct# Full Name       Status Subject                        Messages\n");
    printf("------ ----- --------------- ------ ------------------------------ --------\n");
}

void displayAccountDetailRecord(const struct Account *account)
{
    char *acc_type = NULL;

    if (account->type == 'A')
        acc_type = "AGENT";

    if (account->type == 'C')
        acc_type = "CUSTOMER";

    char TMP_PSS[MAX_PASSWORD_LEN + 1] = {0};

    int x = 0;

    while (account->login.password[x + 1])
    {
        TMP_PSS[x] = account->login.password[x];

        TMP_PSS[x + 1] = '*';

        x += 2;
    }

    printf("%05d %-9s %-15s %5d %11.2lf %-10s %-10s %8s\n",
           account->id, acc_type, account->person.fullname, account->person.birth_year, account->person.household_income,
           account->person.country, account->login.username, TMP_PSS);
}

void displayTicketDetailRecord(const struct Ticket *ticket)
{
    char *status = (ticket->status) ? "ACTIVE" : "CLOSED";

    printf("%06d %05d %-15s %-6s %-30s %5d\n", ticket->id, ticket->customer_acc_id, ticket->messages[0].auth_name,
           status, ticket->subject, ticket->num_of_msg);
}

void applicationStartup(struct AccountTicketingData *account_ticketing_data)
{
    while (1)
    {
        int Index = menuLogin(account_ticketing_data->accounts, account_ticketing_data->ACCOUNT_MAX_SIZE);
        
        if (Index == -1)

            return;

        else if (account_ticketing_data->accounts[Index].type == 'A')
        {
            printf("\n");

            menuAgent(account_ticketing_data, &account_ticketing_data->accounts[Index]);
        }
        else
        {
            printf("ERROR:  Login failed!\n\n");

            pauseExecution();
        }
    }
}

int menuLogin(const struct Account accounts[], int maxn_accounts)
{
    while (1)
    {
        printf("==============================================\n");

        printf("Account Ticketing System - Login\n");

        printf("==============================================\n");

        printf("1) Login to the system\n");

        printf("0) Exit application\n");

        printf("----------------------------------------------\n\n");

        printf("Selection: ");

        int Select = getIntFromRange(0, 1);

        printf("\n");

        if (Select == 1)

        {
            int RES = authenticate(accounts, maxn_accounts);

            if (RES == 0)
            {
                printf("ERROR:  Access Denied.\n\n");

                pauseExecution();
            }

            else

                return RES;
        }
        else
        {
            printf("Are you sure you want to exit? ([Y]es|[N]o): ");

            char C = getCharOption("yYnN");

            printf("\n");

            if (C == 'n' || C == 'N')

                continue;

            else

            {
                printf("==============================================\n");

                printf("Account Ticketing System - Terminated\n");

                printf("==============================================\n");

                return -1;
            }
        }
    }
}

void menuAgent(struct AccountTicketingData *account_ticketing_data, const struct Account *agent)
{
    while (1)
    {
        printf("AGENT: %s (%d)\n", agent->person.fullname, agent->id);

        printf("==============================================\n");

        printf("Account Ticketing System - Agent Menu\n");

        printf("==============================================\n");

        printf("1) Add a new account\n");

        printf("2) Modify an existing account\n");

        printf("3) Remove an account\n");

        printf("4) List accounts: detailed view\n");

        printf("----------------------------------------------\n");

        printf("5) List new tickets\n");

        printf("6) List active tickets\n");

        printf("7) List closed tickets\n");

        printf("8) Add a new ticket\n");

        printf("9) Manage a ticket\n");

        printf("----------------------------------------------\n");

        printf("0) Logout\n\n");

        printf("Selection: ");

        int Option = getIntFromRange(0, 9);

        printf("\n");

        if (Option == 1)

        {
            int IDX = findEmptyAccountIndex(account_ticketing_data->accounts, account_ticketing_data->ACCOUNT_MAX_SIZE);

            if (IDX == -1)
                printf("ERROR: Account listing is FULL, call ITS Support!\n\n");

            else
                getAccount(&account_ticketing_data->accounts[IDX]);

            pauseExecution();

        }
        else if (Option == 2)
        {
            int IDX = findAccountIndexByAcctNum(0, account_ticketing_data->accounts, account_ticketing_data->ACCOUNT_MAX_SIZE, 1);

            printf("\n");

            if (IDX == -1)

                printf("ERROR: Not Found\n");

            else

                updateAccount(&account_ticketing_data->accounts[IDX]);
        }
        else if (Option == 3)
        {
            int IDX = findAccountIndexByAcctNum(0, account_ticketing_data->accounts, account_ticketing_data->ACCOUNT_MAX_SIZE, 1);

            if (IDX == -1)
                printf("ERROR: Not Found\n");

            else
            {
                printf("\n");

                displayAccountDetailHeader();
                displayAccountDetailRecord(&account_ticketing_data->accounts[IDX]);

                printf("\n");
                printf("Are you sure you want to remove this record? ([Y]es|[N]o): ");

                char C = getCharOption("YN");

                printf("\n");

                if (C == 'Y')
                {
                    int x;
                    int CNT = 0;

                    for (x = 0; x < account_ticketing_data->TICKET_MAX_SIZE; x++)

                    {
                        if (account_ticketing_data->tickets[x].customer_acc_id == account_ticketing_data->accounts[IDX].id)

                        {
                            account_ticketing_data->tickets[x].id = 0;
                            account_ticketing_data->tickets[x].customer_acc_id = 0;
                            account_ticketing_data->tickets[x].status = 0;
                            account_ticketing_data->tickets[x].num_of_msg = 0;

                            CNT++;
                        }
                    }

                    account_ticketing_data->accounts[IDX].id = 0;

                    printf("*** Account Removed! (%d ticket(s) removed) ***\n\n", CNT);
                }
            }

            pauseExecution();
        }
        else if (Option == 4)
        {
            displayAllAccountDetailRecords(account_ticketing_data->accounts, account_ticketing_data->ACCOUNT_MAX_SIZE);
            
            pauseExecution();
        }

        else if (Option == 6)

        {
            int IDX;

            do

            {
                displayAllActiveTickets(account_ticketing_data->tickets, account_ticketing_data->TICKET_MAX_SIZE);

                IDX = getTicketNumberToViewMessages(account_ticketing_data->tickets, account_ticketing_data->TICKET_MAX_SIZE, ACTIVE);
                
                if (IDX >= 0)
                    displayMessagesFor(&account_ticketing_data->tickets[IDX]);
            
            } 
            while (IDX != -2);

        }
        else if (Option == 8)
        {
            int Customer_IDX = findAccountIndexByAcctNum(0, account_ticketing_data->accounts, account_ticketing_data->ACCOUNT_MAX_SIZE, 1);

            printf("\n");
            
            if (account_ticketing_data->accounts[Customer_IDX].type == 'A')
                printf("ERROR: Agent accounts can't have tickets!\n\n");
            
            else
                
                addNewTicket(account_ticketing_data->tickets, &account_ticketing_data->accounts[Customer_IDX], account_ticketing_data->TICKET_MAX_SIZE);
            pauseExecution();
        }

        else if (Option == 9)

        {

            menuTicket(account_ticketing_data->tickets, agent, account_ticketing_data->TICKET_MAX_SIZE);

        }

        else

        {
            
            printf("### LOGGED OUT ###\n\n");

            return;

        }
    }
}

void menuTicket(struct Ticket tickets[], const struct Account* agent, int max_tickets)
{
    printf("Enter ticket number: ");

    int Ticket_N = getInteger();

    printf("\n");

    int IDX = findTicketByid(Ticket_N, tickets, max_tickets);

    if (IDX < 0)
    {
        printf("ERROR: Invalid ticket number.\n\n");

        return;
    }

    while (1)

    {
        printf("----------------------------------------\n");

        printf("Ticket %06d - Update Options\n", tickets[IDX].id);

        printf("----------------------------------------\n");

        printf("Status  : %s\n", (tickets[IDX].status) ? "ACTIVE" : "CLOSED");

        printf("Subject : %s\n", tickets[IDX].subject);

        printf("Acct#   : %d\n", tickets[IDX].customer_acc_id);

        printf("Customer: %s\n", tickets[IDX].messages[0].auth_name);

        printf("----------------------------------------\n");

        printf("1) Add CUSTOMER message\n");
        
        printf("2) Add AGENT message\n");

        printf("3) Close ticket\n");
        
        printf("4) Re-activate ticket\n");
        
        printf("0) Done\n");
        
        printf("Selection: ");

        int Option = getIntFromRange(0, 4);
        
        printf("\n");
        
        if(Option == 1 || Option == 2)
        {
            if(!tickets[IDX].status)
                printf("ERROR: Ticket is closed - new messages are not permitted.\n\n");
            
            else if(tickets[IDX].num_of_msg == MAX_MSG_SIZE)
                printf("ERROR: Message limit has been reached, call ITS Support!\n\n");
            
            else
            {
                printf("Enter the ticket message details (150 chars. maximum). Press the ENTER key to submit:\n");
            
                getCString(tickets[IDX].messages[tickets[IDX].num_of_msg].details, 1, MAX_MSG_DETAILS_LEN);
                
                printf("\n");
                
                if(Option == 1)
                {
                    tickets[IDX].messages[tickets[IDX].num_of_msg].auth_acc_type = tickets[IDX].messages[0].auth_acc_type;
                    
                    strcpy(tickets[IDX].messages[tickets[IDX].num_of_msg].auth_name, tickets[IDX].messages[0].auth_name);
                }
                else
                {
                    tickets[IDX].messages[tickets[IDX].num_of_msg].auth_acc_type = agent->type;
                    
                    strcpy(tickets[IDX].messages[tickets[IDX].num_of_msg].auth_name, agent->person.fullname);                    
                }
                
                tickets[IDX].num_of_msg++;
            }
        }

        else if(Option == 4)
        
        {
            
            if(tickets[IDX].status)
        
                printf("ERROR: Ticket is already active!\n\n");
            
            else
            {
            
                printf("Are you sure you want to RE-ACTIVATE this closed ticket? ([Y]es|[N]o): ");
                
                char ANS = getCharOption("YN");
                
                printf("\n");
                
                if(ANS == 'Y')
                {
                
                    tickets[IDX].status = 1;
                    
                    printf("*** Ticket re-activated! ***\n\n");
                }
            }
        }
        
        else
        
            return;
    }
}

int searchAccount(int id, const struct Account accounts[], int maxn_accounts)
{
    int x;
    
    for (x = 0; x < maxn_accounts; x++)
        if (accounts[x].id == id)
            
            return x;
    
    return -1;
}

int findAccountIndexByAcctNum(int id, const struct Account accounts[], int maxn_accounts, int type)
{
    if (type == 0)
    
        return searchAccount(id, accounts, maxn_accounts);
    
    else
    {
        printf("Enter the account#: ");
     
        int Acc_N = getInteger();
        
        return searchAccount(Acc_N, accounts, maxn_accounts);
    }
}

void displayAllAccountDetailRecords(const struct Account accounts[], int maxn_accounts)
{
    int x;
    
    displayAccountDetailHeader();
    
    for (x = 0; x < maxn_accounts; x++)
    
    {
    
        if (accounts[x].id > 0)
            displayAccountDetailRecord(&accounts[x]);
    }
    
    printf("\n");
}

void displayAllNewTickets(const struct Ticket tickets[], int max_size)
{
    displayTicketDetailHeader();
    
    int x;
    
    for (x = 0; x < max_size; x++)
    {
    
        if (tickets[x].id > 0 && tickets[x].status && tickets[x].num_of_msg == 1)
        displayTicketDetailRecord(&tickets[x]);
    
    }

    printf("------ ----- --------------- ------ ------------------------------ --------\n");
}

void displayAllActiveTickets(const struct Ticket tickets[], int max_size)
{
    displayTicketDetailHeader();
    
    int x;
    
    for (x = 0; x < max_size; x++)
    
    {
    
        if (tickets[x].id > 0 && tickets[x].status)
            displayTicketDetailRecord(&tickets[x]);
    
    }
    printf("------ ----- --------------- ------ ------------------------------ --------\n");
}

void displayAllClosedTickets(const struct Ticket tickets[], int max_size)
{
    displayTicketDetailHeader();
    
    int x;
    
    for (x = 0; x < max_size; x++)
    
    {
    
        if (tickets[x].id > 0 && !tickets[x].status)
            displayTicketDetailRecord(&tickets[x]);
    
    }
    printf("------ ----- --------------- ------ ------------------------------ --------\n");
}

void displayMessagesFor(const struct Ticket *ticket)
{
    char *status = (ticket->status) ? "ACTIVE" : "CLOSED";
    
    printf("================================================================================\n");
    printf("%06d (%s) Re: %s\n", ticket->id, status, ticket->subject);
    printf("================================================================================\n");
    
    int x;

    for (x = 0; x < ticket->num_of_msg; x++)
    
    {
    
        char *type = (ticket->messages[x].auth_acc_type == 'C') ? "CUSTOMER" : "AGENT";
        
        printf("%s (%s):\n", type, ticket->messages[x].auth_name);
        printf("   %s\n\n", ticket->messages[x].details);
    
    }
    
    pauseExecution();
}

int getTicketNumberToViewMessages(const struct Ticket tickets[], int max_size, int type)
{
    int Ticket_Id;
    
    printf("\n");
    printf("Enter the ticket number to view the messages or\n");
    printf("0 to return to previous menu: ");
    
    scanf("%d", &Ticket_Id);
    
    clearStandardInputBuffer();
    
    printf("\n");
    
    if (Ticket_Id == 0)
        return -2;
    
    int IDX = findTicketByid(Ticket_Id, tickets, max_size);
    
    if (IDX == -1)
    
    {
    
        printf("ERROR: Invalid ticket number.\n\n");
        
        pauseExecution();
        
        return -1;
    }
    
    if (type == NEW && tickets[IDX].id > 0 && tickets[IDX].status && tickets[IDX].num_of_msg == 1)
        return IDX;
    
    if (type == ACTIVE && tickets[IDX].id > 0 && tickets[IDX].status)
        return IDX;
    
    if (type == CLOSED && tickets[IDX].id > 0 && !tickets[IDX].status)
        return IDX;
    
    printf("ERROR: Invalid ticket number.\n\n");
    
    pauseExecution();
    
    return -1;
}

int findTicketByid(int ticket_id, const struct Ticket tickets[], int max_size)
{
    int x;
    
    for (x = 0; x < max_size; x++)
    
    {
    
        if (tickets[x].id == ticket_id)
        
        {
        
            return x;
        
        }
    }
    
    return -1;
}

int findEmptyAccountIndex(const struct Account accounts[], int maxn_accounts)
{
    int x;

    for (x = 0; x < maxn_accounts; x++)
    
        if (accounts[x].id == 0)

            return x;

    return -1;

}

int findEmptyTicketIndex(const struct Ticket tickets[], int max_tickets)
{
    int x;
   
    for (x = 0; x < max_tickets; x++)
        if (tickets[x].id == 0)
            return x;
    
    return -1;
}

void addNewTicket(struct Ticket tickets[], const struct Account *account, int max_tickets)
{
    int IDX = findEmptyTicketIndex(tickets, max_tickets);
    
    if (IDX == -1)
    
    {
    
        printf("ERROR: Ticket listing is FULL, call ITS Support!\n");
        
        return;
    
    }
    
    displayAccountDetailHeader();
    displayAccountDetailRecord(account);
    
    printf("\nAdd a new ticket for this customer? ([Y]es|[N]o): ");
    
    char ANS = getCharOption("YN");
    
    printf("\n");
    
    if (ANS == 'Y')
    
    {
        
        tickets[IDX].id = 70534;
        tickets[IDX].customer_acc_id = account->id;
        tickets[IDX].status = 1;
        tickets[IDX].num_of_msg = 1;
        tickets[IDX].messages[0].auth_acc_type = account->type;
        
        strcpy(tickets[IDX].messages[0].auth_name, account->person.fullname);

        printf("New Ticket (Ticket#:%06d)\n", tickets[IDX].id);
        printf("----------------------------------------\n");
        printf("Enter the ticket SUBJECT (30 chars. maximum): ");
        
        getCString(tickets[IDX].subject, 1, MAX_TICKET_SUBJECT_LEN);
        
        printf("\nEnter the ticket message details (150 chars. maximum). Press the ENTER key to submit:\n");
        
        getCString(tickets[IDX].messages[0].details, 1, MAX_MSG_DETAILS_LEN);
        
        printf("\n");
        
        printf("*** New ticket created! ***\n\n");
 
    }

}

// Pause execution until user enters the enter key
void pauseExecution(void)
{
    printf("<< ENTER key to Continue... >>");
   
    clearStandardInputBuffer();
    
    putchar('\n');
}