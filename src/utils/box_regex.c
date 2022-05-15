#include "box_regex.h"

/* // For testing
int main() {
    
    char* string = box_get_regex_match("\t\t\t<p class=hola>que pasa chaval",AFTER_TAG);

    if(string != NULL) {

        printf("MATCH: %s\n", string);
        free(string);
    }
    else {

        printf("NOT MATCH FOUND\n");
    }
    
    return 0;
}
*/


extern char *box_move_regex_match(char *string, const char *expr) {

    regex_t regex;
    regmatch_t regmatch[2];

    int res;

    if ((res = regcomp(&regex, expr, REG_EXTENDED)) != 0) {

        printf("regcomp() failed\n");
        exit(EXIT_FAILURE);
    }

    res = regexec(&regex, string, 2, regmatch, 0);

    if (res == 0) {

        int index = 0;

        if (regmatch[1].rm_eo != -1) index = 1;

        string += regmatch[index].rm_so;

    }

    return string;
}



extern char *box_get_regex_match(const char *string, const char *expr) {

    regex_t regex;
    regmatch_t regmatch[2];

    char *match = NULL;
    int   res;

    if ((res = regcomp(&regex, expr, REG_EXTENDED)) != 0) {

        printf("regcomp() failed\n");
        exit(EXIT_FAILURE);
    }

    res = regexec(&regex, string, 2, regmatch, 0);

    if (res == 0) {

        int index = 0;

        if (regmatch[1].rm_eo != -1) index = 1;

        int size = regmatch[index].rm_eo - regmatch[index].rm_so;

        match = (char*)calloc(size+1, sizeof(char));
        strncpy(match, string + regmatch[index].rm_so, size);

    }

    return match;
}


extern int box_check_regex_match(const char *string, const char *expr) {

    regex_t regex;
    regmatch_t regmatch[2];

    int res = 1;

    if ((res = regcomp(&regex, expr, REG_EXTENDED)) != 0) {

        printf("regcomp() failed\n");
        exit(EXIT_FAILURE);
    }

    res = regexec(&regex, string, 2, regmatch, 0);

    return res;
}

extern char *box_concat_n_destroy(char *dest, char *src) {
    
    char *string = NULL;

    // ASSERT dest and src are not null
    if ( dest != NULL && src != NULL) {
        
        string = (char*)malloc(sizeof(char)*(strlen(dest) + strlen(src) + 1));
        
        strncpy(string, dest, strlen(dest));
        strcat(string, src);

        free(dest);
        free(src);
    }

    return string;
}


extern char *box_copy_string(const char *src) {

    if (src == NULL) return NULL; 

    char* string = (char*)calloc(strlen(src)+1, sizeof(char));
    strncpy(string, src, strlen(src));

    return string;
}

