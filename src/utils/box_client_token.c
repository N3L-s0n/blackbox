#include "box_client_token.h"

typedef struct box_token {

    char value[TOKENSIZE + 1];
    size_t size;

} box_token;

static char get_random_char(void);

static const char alphanum[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxzy@#$*+-.";

static char get_random_char(void){

    return alphanum[rand() % (sizeof(alphanum) - 1)];
}

extern box_token *box_new_token(char *value) {

    if (value == NULL || strlen(value) != TOKENSIZE) return NULL;

    box_token *token = (box_token *)calloc(1, sizeof(box_token));

    strncpy(token->value, value, TOKENSIZE);
    token->size = TOKENSIZE;

    return token; 
}

extern void box_destroy_token(box_token *token) {

    if (token != NULL) free(token);
}

extern box_token *box_craft_token(void) {

    char value[TOKENSIZE + 1];
    long seconds;

    time(&seconds);
    srand((unsigned int)seconds);

    for (int i=0; i<TOKENSIZE; i++) {

        value[i] = get_random_char();
    }

    value[TOKENSIZE] = MYNULL;

    box_token *token = box_new_token(value);

    return token;
}

extern char *box_get_token_value(box_token *token) {

    if (token == NULL) return NULL;

    return token->value;
}

extern char * box_get_timestamp(){
    time_t seconds = time(NULL);
    char * str = calloc(100,sizeof(char));
    snprintf(str,100,"%ld",seconds);        
    return str;
}

extern int box_check_time(char * time){
    unsigned long int time_1 = atol(time);
    unsigned long int time_2 = atol(box_get_timestamp());
    unsigned long int rest = time_2 -time_1;
    if (rest>=3600){
        return 1;
    }
    if (rest<0)printf("hola");
    return 0; 
}

 
