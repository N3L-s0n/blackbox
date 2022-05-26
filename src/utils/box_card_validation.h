#ifndef BOX_CREDIT_CARD_VALIDATION_H
#define BOX_CREDIT_CARD_VALIDATION_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

extern int validateCard(char* number, int month, int year, char* csv);
extern int validCSV(char* csv);
extern int validDate(int month, int year);
extern int validNumber(long long cardnumber);

#endif