#include "box_entry_validation.h"

extern int validate_entry(char* entry){
    return !box_check_regex_match(entry,VALID_ENTRY);
}

extern int validate_password(char* password){
    char *p = password;
    char c;
    int nupper = 0;
    int nlower = 0;
    int ndigit = 0;
    int nspecial = 0;
    while (*p) {
        c = *p++;
        if (isupper(c)) ++nupper;
        else if (islower(c)) ++nlower;
        else if (isdigit(c)) ++ndigit;
        else if (ispunct(c)) ++nspecial;
        else continue; // space character
   }

   return nupper && nlower && ndigit && nspecial;
}


extern int validate_length(char* entry, int length){
    if(entry==NULL) return 0;
    
    return strlen(entry) <= length;
}

