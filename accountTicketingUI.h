/*
    ==================================================
    Assignment #2 Milestone #2
    ==================================================
    Name   : Shayan Chabook
    ID     : 159844208
    Email  : Schabook@myseneca.ca
    Section: ZAA
*/
#ifndef ACCOUNT_TICKETING_UI_H_
#define ACCOUNT_TICKETING_UI_H_

#include "account.h"
#include "ticket.h"

#define NEW 2
#define ACTIVE 1
#define CLOSED 0

struct AccountTicketingData
{

    struct Account *accounts;
    // array of accounts

    const int ACCOUNT_MAX_SIZE; // maximum elements for account array
    
    struct Ticket *tickets;
    
    const int TICKET_MAX_SIZE;
    // array of tickets
    // maximum elements for ticket array

};

void displayAccountDetailHeader(void);

void displayTicketDetailHeader(void);

void displayAccountDetailRecord(const struct Account *account);

void displayTicketDetailRecord(const struct Ticket *ticket);

void displayMessagesFor(const struct Ticket *ticket);

void applicationStartup(struct AccountTicketingData* account_ticketing_data);

int menuLogin(const struct Account accounts[], int maxn_accounts);

void menuAgent(struct AccountTicketingData* account_ticketing_data, const struct Account *agent);

void menuTicket(struct Ticket tickets[], const struct Account* agent, int max_tickets);

int searchAccount(int id, const struct Account accounts[], int maxn_accounts);

int findAccountIndexByAcctNum(int id, const struct Account accounts[], int maxn_accounts, int type);

void displayAllAccountDetailRecords(const struct Account accounts[], int maxn_accounts);

void displayAllNewTickets(const struct Ticket tickets[], int max_size);

void displayAllActiveTickets(const struct Ticket tickets[], int max_size);

void displayAllClosedTickets(const struct Ticket tickets[], int max_size);

int findEmptyAccountIndex(const struct Account accounts[], int maxn_accounts);

int findEmptyTicketIndex(const struct Ticket tickets[], int max_tickets);

int getTicketNumberToViewMessages(const struct Ticket tickets[], int max_size, int type);

int findTicketByid(int ticket_id, const struct Ticket tickets[], int max_size);

void addNewTicket(struct Ticket tickets[], const struct Account* account, int max_tickets);

// Pause execution until user enters the enter key
void pauseExecution(void);

#endif

