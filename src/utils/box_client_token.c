#include "box_client_token.h"

static const char alphanum[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxzy@#$*+-.";
int length= sizeof(alphanum)-1;

extern char getRandomChar(){

    return alphanum[rand()%length];
}

extern char * box_getToken(){
    char token[MYLEN], *ptr;
    int i;
    long seconds;
    time(&seconds);
    srand((unsigned int)seconds);
    for (i=0; i<MYLEN;i++){
        token[i] = getRandomChar();
    }
    token[MYLEN-1]=MYNULL;
    ptr=token;
    return ptr;
}


 