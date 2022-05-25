#ifndef BOX_TOKENS
#define BOX_TOKENS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define TOKENSIZE 200
#define MYNULL '\0'

extern char getRandomChar();
extern char* box_getToken();
extern char* box_get_timestamp();

#endif