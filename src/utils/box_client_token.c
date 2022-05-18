#include "box_client_token.h"
char* generate_token(){
    char token[MYLEN], *ptr;
    int i,num,start,range;
    long seconds;

    start= (int)('!');
    range= (int)('z')-(int)('!');

    time(&seconds);
    srand((unsigned int)seconds);
    for (ptr = token , i=1; i<MYLEN; ++ptr, ++i){
        num = rand()%range;
        *ptr = (char)(num+start);
    }
    *ptr= MYNULL;
    printf(token);
    return token;
}


 