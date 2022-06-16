#ifndef BOX_ENTRY_VALIDATION_H
#define BOX_ENTRY_VALIDATION_H

#include "box_regex.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>


extern int validate_entry(char* entry);
extern int validate_password(char* password);
extern int validate_length(char* entry, int length);



#endif