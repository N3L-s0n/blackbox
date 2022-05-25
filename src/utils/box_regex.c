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

extern char *box_replace_variables(char *variables, char *target) {

    //char *text = box_copy_string(target);
    char *text = target;

    char *variables_tmp = variables;
    char *text_tmp = NULL;
    
    while (variables_tmp != NULL) {

        while(1) {

            text_tmp = box_replace_regex_match(variables_tmp, text);

            if (text_tmp == NULL) break;

            free(text);
            text = text_tmp;
        }

        variables_tmp = box_move_regex_match(variables_tmp, VAR_VALUE);
    }

    return text;
}

/* vars should be in format: varname=var
 * replaces in string: $(varname) -> var */
extern char *box_replace_regex_match(const char *vars, const char *string) {

    regex_t regex;
    regmatch_t regmatch[2];

    char *_new = NULL;
    int   res;

    char *varname = box_get_regex_match(vars, VAR_NAME);
    char *var     = box_get_regex_match(vars, VAR_VALUE);

    if (varname == NULL) return NULL;
    if (var == NULL) var = (char*)calloc(1, sizeof(char));

    int size = strlen(varname) + 20;
    char *buffer = (char*)calloc(size + 1, sizeof(char)); 
    snprintf(buffer, size, "([$][(]%s[)])", varname);


    if ((res = regcomp(&regex, buffer, REG_EXTENDED)) != 0) {

        printf("regcomp() failed\n");
        exit(EXIT_FAILURE);
    }

    res = regexec(&regex, string, 2, regmatch, 0);
    regfree(&regex);

    if (res == 0) {

        int index = 0;

        if (regmatch[1].rm_eo != -1) index = 1;

        int size = regmatch[index].rm_eo - regmatch[index].rm_so;
        
        _new = (char*)calloc(strlen(string) + (strlen(var) - size), sizeof(char));

        strncpy(_new, string, regmatch[index].rm_so);
        strncpy(_new+regmatch[index].rm_so, var, strlen(var));
        strncpy(_new+regmatch[index].rm_so+strlen(var), string+regmatch[index].rm_eo, strlen(string+regmatch[index].rm_eo));
    }

    free(var);
    free(varname);
    free(buffer);

    return _new;

}

extern char *box_move_regex_match(char *string, const char *expr) {

    regex_t regex;
    regmatch_t regmatch[2];

    int res;

    if ((res = regcomp(&regex, expr, REG_EXTENDED)) != 0) {

        printf("regcomp() failed\n");
        exit(EXIT_FAILURE);
    }

    res = regexec(&regex, string, 2, regmatch, 0);
    regfree(&regex);

    if (res == 0) {

        int index = 0;

        if (regmatch[1].rm_eo != -1) index = 1;

        string += regmatch[index].rm_so;

    }
    else return NULL;

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
    regfree(&regex);

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
    regfree(&regex);

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

extern int box_same_string(char* string, char * string2){
    return strcmp(string,string2);
}

extern char * box_replace_string(char *str,char * pattern, char * replace){
    int i = 0, cnt = 0;
    int len1 = strlen(replace);
    int len2 = strlen(pattern);
    for (i = 0; str[i] != '\0'; i++) {
        if (strstr(&str[i], pattern) == &str[i]) {
            cnt++;
            i += len2 - 1;
        }
    }
    char *newString = (char *)calloc(i + cnt * (len1 - len2) + 1, sizeof(char));
    i = 0;
    while (*str) {
        if (strstr(str, pattern) == str) {
            strcpy(&newString[i], replace);
            i += len1;
            str += len2;
        }
        else
        newString[i++] = *str++;
    }
    return newString;
}
/*
extern char ** box_strtok_string(char * string, char * separator){
    char *ptr[3];
    char * token;
    token = strtok(string,separator);
    int i=0;
    while ((i<3) || (token=!NULL) ){
        ptr[i] = token;
        i++;
        strtok(string,separator);
    }

    return ptr;  
}*/
