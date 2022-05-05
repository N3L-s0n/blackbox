#include "box_reader.h"

/* declarations */

static void box_set_tag(box_file file, char *line);

static int box_check_void_tag(const char *string);

static int box_check_end_tag(const char *string);

static char *box_concat(char *dest, char *src);

static char *box_move_regex_line(box_regex_result result, char *string);

static char *box_get_tag_body(box_regex_result result, char *string);

static char *box_get_regex_string(box_regex_result result, const char *string);

static char *box_handle_tag(box_file file, box_regex_result result, char *tmpline);

static char *box_handle_element(box_file file, char *tmpline);

static char *box_match_tag_name(const char* string);

static box_regex_result box_match_tag(const char *string);

/* definitions */

extern box_file box_read_file(char *filename) {

    ssize_t read;

    char *line;
    char *tmpline = NULL;
    size_t len;

    FILE *fp = fopen(filename, "r");

    if (fp == NULL) {
        fprintf(stderr, "Could not open file %s\n", filename);
        exit(1);
    }
    
    box_file file = box_new_html_tree();

    int i = 0;

    box_regex_result result;

    while ((read = getline( &line, &len, fp)) != -1) {

        tmpline = line;

        int skip = 0;
        while (skip == 0) {
            
            result = box_match_tag(tmpline);
            if (result.res == 0) {
               
                tmpline = box_handle_tag(file, result, tmpline);
            }
            else {

                if(strlen(tmpline) > 1) {
                    box_handle_element(file, tmpline);
                }
                skip = 1;
            }
        }

        i++;
    }

    if (line != NULL) {
        free(line);
    }

    return file;
}

extern void box_destroy_file(box_file file) {

    box_destroy_html_tree(file);
}

static char* box_handle_element(box_file file, char* tmpline) {
    
    element el = box_html_tree_add_node(file);
    box_html_set_opening_tag(el, tmpline);

    box_html_element_up(file);
}

static char* box_handle_tag(box_file file, box_regex_result result, char *tmpline) {

    char *match;
    char *body;

    match = box_get_regex_string(result, tmpline);
    body = box_get_tag_body(result, tmpline);

    if (box_check_void_tag(match) == 0) {       // VOID TAG
                                                //
        element el = box_html_tree_add_node(file);
        box_html_set_opening_tag(el, match);

        box_set_tag(file, match);
        box_html_element_up(file);

        if (body != NULL) {
            free(body); 
        }
    }
    else if (box_check_end_tag(match) == 0) {   // END TAG
        
        element el = box_html_get_last_element(file);
        box_html_set_closing_tag(el, match);
       
        box_handle_element(file, body);

        box_html_element_up(file);
    }
    else {                                      // START TAG
        
        element el = box_html_tree_add_node(file);
        box_html_set_opening_tag(el, match);

        box_set_tag(file, match);

        if (body != NULL) {
            free(body); 
        }
    }
    
    return box_move_regex_line(result, tmpline);
}

static void box_set_tag(box_file file, char *line) {
    
    char *string = box_match_tag_name(line);

    if (string != NULL) {
        
        box_html_set_html_tag(box_html_get_last_element(file), box_html_tag_id(string));
        free(string);
    }

}

static char *box_concat(char *dest, char *src) {
    
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

static char *box_move_regex_line(box_regex_result result, char *string) {

    string += result.regmatch[1].rm_eo;

    return string;
}

static char *box_get_tag_body(box_regex_result result, char *string) {

    int size;
    char *body;

    size = result.regmatch[1].rm_so;

    body = (char*)malloc(sizeof(char)*(size+1));

    strncpy(body, string, size);
    body[size] = '\0';

    return body;
}


static char *box_get_regex_string(box_regex_result result, const char *string) {

    int size;
    char *match;

    size = result.regmatch[1].rm_eo - result.regmatch[1].rm_so;

    match = (char*)malloc(sizeof(char)*(size+1));

    strncpy(match, string + result.regmatch[1].rm_so, size);
    match[size] = '\0';

    return match;
}

static int box_check_void_tag(const char* string) {

    regex_t regex;

    int result;

    if( 0 != (result = regcomp(&regex, "(/>)", REG_EXTENDED))) {
        printf("regcomp() failed\n");
        exit(EXIT_FAILURE);
    }
    result = regexec(&regex, string, 0, NULL, 0);
 
    return result;
}

static int box_check_end_tag(const char* string) {

    regex_t regex;

    int result;

    if( 0 != (result = regcomp(&regex, "(</)", REG_EXTENDED))) {
        printf("regcomp() failed\n");
        exit(EXIT_FAILURE);
    }
    result = regexec(&regex, string, 0, NULL, 0);
 
    return result;
}

static box_regex_result box_match_tag(const char* string) {

    regex_t regex; 

    box_regex_result result; 

    static regmatch_t regmatch[2];

    if( 0 != (result.res = regcomp(&regex, "(<[^>]+>)", REG_EXTENDED))) {
        printf("regcomp() failed\n");
        exit(EXIT_FAILURE);
    }
    result.res = regexec(&regex, string, 2, regmatch, 0);
   

    result.regmatch = regmatch;

    return result;
}

static char *box_match_tag_name(const char* string) {

    regex_t regex;

    box_regex_result result;

    static regmatch_t regmatch_name[2];

    if( 0 != (result.res = regcomp(&regex, "<([a-zA-Z0-9]+).*>", REG_EXTENDED))) {
        printf("regcomp() failed\n");
        exit(EXIT_FAILURE);
    }

    result.res = regexec(&regex, string, 2, regmatch_name, 0);

    if (result.res != 0) {
        return NULL;
    }

    result.regmatch = regmatch_name;
 
    return box_get_regex_string(result, string);

}

static char *box_match_class(const char* string) {

    regex_t regex;

    box_regex_result result;

    static regmatch_t regmatch_class[2];

    if( 0 != (result.res = regcomp(&regex, "<.*[:space:]class=\"([a-zA-Z0-9]+)\".*>", REG_EXTENDED))) {
        printf("regcomp() failed\n");
        exit(EXIT_FAILURE);
    }

    result.res = regexec(&regex, string, 2, regmatch_class, 0);

    if (result.res != 0) {
        return NULL;
    }

    result.regmatch = regmatch_class;
 
    return NULL;

}
