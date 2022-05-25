#include "box_client_token.h"

static const char alphanum[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxzy@#$*+-.";
int length= sizeof(alphanum)-1;

extern char getRandomChar(){

    return alphanum[rand()%length];
}

extern char * box_getToken(){
    char token[TOKENSIZE], *ptr;
    int i;
    long seconds;
    time(&seconds);
    srand((unsigned int)seconds);
    for (i=0; i<TOKENSIZE;i++){
        token[i] = getRandomChar();
    }
    token[TOKENSIZE-1]=MYNULL;
    ptr=token;
    return ptr;
}

extern char * box_get_timestamp(){
    time_t seconds = time(NULL);
    char * str = calloc(100,sizeof(char));
    snprintf(str,100,"%ld",seconds);        
    return str;
}

extern int box_compare_time(char * time1,char *time2){
    long int time_1 = atoi(time1);
    long int time_2 = atoi(time2);
    if (time_1<time_2){
        return 1; 
    }
    return 0; 
}


 