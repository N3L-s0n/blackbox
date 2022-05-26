#include "box_card_validation.h"


extern int validateCard(char* number, int month, int year, char* csv){
    long long num = atoll(number); 

    return validCSV(csv) && validDate(month,year) && validNumber(num);
}

extern int validCSV(char* csv){
    return atoi(csv) >= 0 && atoi(csv) <= 999;
}

extern int validDate(int month, int year){
    char currentYear[5] = {0};
    char currentMonth[3] = {0};
    time_t rawtime = time(NULL);
    struct tm *ptm = localtime(&rawtime);
    strftime(currentMonth, 3, "%m", ptm);
    strftime(currentYear, 5, "%y", ptm);

    if(atoi(currentYear)+2000 == year && month <= atoi(currentMonth)) return 0;

    if(month <= 0 || month >= 13) return 0;

    if(year < atoi(currentYear)+2000) return 0;
    
    return 1;
}


extern int validNumber(long long cardnumber)
{
    // Determine whether it has a valid number of digits
    int count = 0;
    long long digits = cardnumber;

    //checks for card length of 13, 15, or 16
    long long length = cardnumber;
    while (length > 0)
    {
        length = length/10;
        count++;
    }

    printf("Count %d\n",count);

    if ((count != 13) && (count != 15) && (count != 16))
    {
        return 0;
    }
    // create array size with the count of the number
    
    int number[count];
  
    // store each digit of card number in the array number
    for (int i = 0; i < count; i++)
    {
        number[i] = cardnumber % 10;
        cardnumber = cardnumber / 10;
    }

    int cardarray[count];
    for (int i = 1; i < count; i++)
    {
        cardarray[i] = number[i];
    }
    // multiply every other number in the array
    for (int i = 1; i < count; i+=2)
    {
        number[i] = number[i] * 2;
    }

    int accumulator = 0;
    int sumdigit;
    
    if (count == 13)
    {
      for (int i = 0; i < count; i++)
      {
        sumdigit = (number[i] % 10) + (number[i]/10 % 10);
        accumulator = accumulator + sumdigit;
      }
      if (cardarray[12] == 4 && accumulator % 10 == 0)
      {
        //printf("VISA\n");
        return 1;
      }
      else
      {
        //printf("INVALID\n");
        return 1;
      }
    }
    if (count == 15)
    {
      for (int i = 0; i < count; i++)
      {
        sumdigit = (number[i] % 10) + (number[i]/10 % 10);
        accumulator = accumulator + sumdigit;
      }
      if (cardarray[14] == 3 && accumulator % 10 == 0 && (cardarray[13] == 4 || cardarray[13] == 7))
      {
        //printf("AMEX\n");
        return 1;
      }
      else
      {
        //printf("INVALID\n");
        return 0;
      }
    }
    if (count == 16)
    {
      for (int i = 0; i < count; i++)
      {
        sumdigit = (number[i] % 10) + (number[i]/10 % 10);
        accumulator = accumulator + sumdigit;
      }
      if (cardarray[15] == 4 && accumulator % 10 == 0)
      {
        //printf("VISA\n");
        return 1;
      }
      else if (cardarray[15] == 5 && accumulator % 10 == 0 && (cardarray[14] == 1 || cardarray[14] == 2 || cardarray[14] == 3 || cardarray[14] == 4 || cardarray[14] == 5))
        {
            //printf("MASTERCARD\n");
            return 1;
        }
      else
      {
        //printf("INVALID\n");
        return 0;
      }
    }
  
    return 0;
} 

