/*
    ==================================================
    Assignment #2 Milestone #2
    ==================================================
    Name   : Shayan Chabook
    ID     : 159844208
    Email  : Schabook@myseneca.ca
    Section: ZAA
*/
#ifndef TICKET_H_
#define TICKET_H_

#define MAX_NAME_LEN 30
#define MAX_MSG_DETAILS_LEN 150
#define MAX_TICKET_SUBJECT_LEN 30
#define MAX_MSG_SIZE 20

struct Message
{
   
    char auth_acc_type;
    char auth_name[MAX_NAME_LEN + 1];
    char details[MAX_MSG_DETAILS_LEN + 1];

};

struct Ticket
{

    int id;
    int customer_acc_id;
    int status;

    char subject[MAX_TICKET_SUBJECT_LEN + 1];

    int num_of_msg;

    struct Message messages[MAX_MSG_SIZE];

};



#endif