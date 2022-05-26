#ifndef BOX_TOKEN_H
#define BOX_TOKEN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define TOKENSIZE 200
#define MYNULL '\0'

typedef struct box_token box_token;

extern box_token *box_new_token(char *value);
extern void   box_destroy_token(box_token *token);

extern box_token* box_craft_token(void);
extern char *box_get_token_value(box_token *token);

#endif
