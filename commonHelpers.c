
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

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "commonHelpers.h"


int thisYear(void)
{
    
    time_t currentTime = time(NULL);
    
    return localtime(&currentTime)->tm_year + 1900;

}

void clearStandardInputBuffer(void)
{
    while (getchar() != '\n')
    {
    
    ; // On purpose: do nothing

    }
}

int getInteger()
{
    char Nl = 'x';
    
    int VALUE;
    
    while (Nl != '\n')
    {
        scanf("%d%c", &VALUE, &Nl);
       
        if (Nl != '\n')
        
        {
        
            clearStandardInputBuffer();
            
            printf("ERROR: Value must be an integer: ");
        
        }
    }
    
    return VALUE;
}

int getPositiveInteger()
{
    int x;
    
    while(1)
    
    {
        x = getInteger();
    
        if(x <= 0)
            printf("ERROR: Value must be a positive integer greater than zero: ");
        
        else
        
            return x;
    }
}

double getDouble()
{
    char Nl = 'x';
    double VALUE;
    
    while (Nl != '\n')
   
    {
        
        scanf("%lf%c", &VALUE, &Nl);
    
        if (Nl != '\n')
        
        {
            
            clearStandardInputBuffer();
        
            printf("ERROR: Value must be a double floating-point number: ");
        }
    }
    
    return VALUE; 
}

double getPositiveDouble()
{
    double x;
    
    while(1)
    
    {
    
        x = getDouble();
        
        if(x <= 0)
            printf("ERROR: Value must be a positive double floating-point number: ");
        
        else
        
            return x;
    
    }
}

int getIntFromRange(int min, int max)
{
    while (1)
    
    {
        
        int VALUE = getInteger();
       
        if (VALUE >= min && VALUE <= max)
            return VALUE;
        
        else
        
            printf("ERROR: Value must be between %d and %d inclusive: ", min, max);
   
    }
}

char getCharOption(char valid_chars[])
{
    int x;
    char Nl = 'x';
    
    while(1)
    
    {
    
        char C;
        
        scanf("%c%c", &C, &Nl);
        
        if(Nl != '\n')
        
        {
        
            printf("ERROR: Character must be one of [%s]: ", valid_chars);
            
            clearStandardInputBuffer();
        
        }
        
        else 
        
        {
            for(x = 0; valid_chars[x]; x++)
                if(C == valid_chars[x])
        
                    return C;
            
            printf("ERROR: Character must be one of [%s]: ", valid_chars);
        
        }
    }
}

void getCString(char* cstr, int min_chars, int max_chars)
{
    int x;
    char STR[100];
   
    while(1)
    
    {
        int LEN;
    
        scanf("%100[^\n]", STR);
        
        for(LEN = 0; STR[LEN] != '\0'; LEN++);
        
        if(min_chars == max_chars && LEN != max_chars)
            printf("ERROR: String length must be exactly %d chars: ", max_chars);
        
        else if(LEN > max_chars)     
            printf("ERROR: String length must be no more than %d chars: ", max_chars);
        
        else if(LEN < min_chars)
            printf("ERROR: String length must be between %d and %d chars: ", min_chars, max_chars);
        
        else 
        
        {
            for(x = 0; x < LEN; x++)
                cstr[x] = STR[x];
        
            cstr[LEN] = '\0';
            
            clearStandardInputBuffer();
            
            return;
        }
        
        clearStandardInputBuffer();
    
    }
}

int checkUser(char *username)
{
	int x;
    for(x = 0; x < strlen(username); x++)
    
    {
    
        if(isspace(username[x]))
        
        {
        
            printf("ERROR:  The user login must NOT contain whitespace characters.\n");
        
            return 0;
        
        }
    }
    return 1;
}

int checkPass(char* password)
{
    int DigitCount = 0;
    int UpperCaseCount = 0;
    int LowerCaseCount = 0;
    int SymbolCount = 0; 
    int i;
    for(i = 0; i < strlen(password); i++)
   
    {
    
        if (islower(password[i])) ++LowerCaseCount;
        
        if (isupper(password[i])) ++UpperCaseCount;
        
        if (isdigit(password[i])) ++DigitCount;
        
        if (isSymbol(password[i])) ++SymbolCount;
    
    }
    
    if(DigitCount == 2 && UpperCaseCount == 2 && LowerCaseCount == 2 && SymbolCount == 2)
        return 1;
    
    else
    
    {
    
        printf("SECURITY: Password must contain 2 of each:\n");
        printf("          Digit: 0-9\n");
        printf("          UPPERCASE character\n");
        printf("          lowercase character\n");
        printf("          symbol character: !@#$%%^&*\n");
        
        return 0;
    
    }

}   

void makeUpper(char* str )
{
    int x;
    for(x = 0; x < strlen(str); x++)
    
        str[x] = toupper(str[x]);

}

int isSymbol(char c)
{
    
    if(c == '!' || c == '@' || c == '#' || c == '$' || c == '%' || c == '^' || c == '&' || c == '*')
        return 1;
   
    return 0;
}


int countDigit(const char* str)
{
    int i, count = 0;


    for (i = 0; str[i] != '\0'; i++)
    {
        if (isdigit(str[i]))
        {
            count++;
        }
    }


    if (count < 2)
    {
        return 1;
    }
    else
    {
        return 0;
    }

}