/*
    ==================================================
    Assignment #2 Milestone #2
    ==================================================
    Name   : Shayan Chabook
    ID     : 159844208
    Email  : Schabook@myseneca.ca
    Section: ZAA
*/
#ifndef COMMON_HELPERS_H_
#define COMMON_HELPERS_H_

int thisYear(void);

void clearStandardInputBuffer(void);

int getInteger(void);

int getPositiveInteger(void);

double getDouble(void);

double getPositiveDouble(void);

int getIntFromRange(int min, int max);

char getCharOption(char valid_chars[]);

void getCString(char* cstr, int min_chars, int max_chars);

int checkUser(char* username);

int checkPass(char* password);

void makeUpper(char* str);

int isSymbol(char c);


#endif