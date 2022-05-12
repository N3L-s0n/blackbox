#include "box_headers.h"

typedef void (*box_header_handler)(unsigned int*, unsigned int);

typedef unsigned int *box_header_values;

static char *box_get_regex_string(regmatch_t* reg, const char *string);

struct box_headers {

    struct box_header_node  *root;   
    struct box_header_node  *last;   
    int                     count;

};

typedef struct box_header_node box_header_node;

struct box_header_node {

   box_header_handler   handler;
   unsigned int         *values;
   unsigned int         count;

   struct box_header_node   *next;
};

static char *box_content_type_values[] = {

    /* BOX_TYPE_TEXT_HTML */
    "text/html",

    /* BOX_TYPE_TEXT_PLAIN */
    "text/plain",

    /* BOX_TYPE_CHARSET_UTF */
    "charset=utf-8"

};

extern box_headers* box_new_headers(void) {
    
    box_headers *headers = (box_headers*)malloc(sizeof(box_headers));

    return headers;
}

static box_header_node* box_add_header(box_headers *headers, box_header_handler handler, unsigned int values_count) {
    
    box_header_node *node = (box_header_node*)malloc(sizeof(box_header_node));

    *node = (box_header_node) {
        .handler = handler,
        .values = (unsigned int*)malloc(sizeof(unsigned int) * values_count),
        .count = 0,
        .next = NULL
    };

    if (headers->last != NULL) {
        headers->last->next = node;
        headers->last = node;
    }
    else {
        headers->root = node;
        headers->last = node;
    }

    headers->count += 1;

    return node;
}

static void box_content_type(unsigned int *values, unsigned int count) {
    
    printf( "%s: ", BOX_CONTENT_TYPE );

    for (int i=0; i<count; ++i) {
        printf("%s%s", box_content_type_values[values[i]], (i+1 == count) ? "" : "; "); 
    }
}


extern void box_header_add_content_type(box_headers *headers, unsigned int *values, unsigned int count) {
   
    box_header_node *node = box_add_header(headers, &box_content_type, count); 

    for (int i = 0; i < count; ++i) {
        node->values[i] = values[i];
    }

    node->count = count;

}

extern void box_print_headers(box_headers *headers) {
    
    box_header_node *node = headers->root;

    while (node != NULL) {
        node->handler(node->values, node->count);
        node = node->next;

        printf("%s", BOX_HEADER_END);
    }

    printf("%s", BOX_HEADER_END);
}

extern void box_destroy_headers(box_headers *headers) {
    
    box_header_node *node = headers->root;
    box_header_node *tmp;

    while (node != NULL) {
        tmp = node; 
        node = node->next;

        free(tmp->values);
        free(tmp);
    }

    free(headers);
}

extern char *box_get_env_var(char *varname, char **env) {

    regex_t regex;
    regmatch_t regmatch[2]; 

    int size = strlen(varname) + 10;

    char *buffer = (char*)malloc(sizeof(char) * size);
    char *var = NULL;

    snprintf(buffer, size, "%s=(.*)", varname);

    if( 0 != regcomp(&regex, buffer, REG_EXTENDED)) {
        printf("regcomp() failed\n");
        exit(EXIT_FAILURE);
    }

    while(*env) {
        
        if (regexec(&regex, *env, 2, regmatch, 0) == 0) {

            var = box_get_regex_string(regmatch, *env);
            break;
        }

        env++;
    }

    free(buffer);

    return var;
}

extern char *box_get_value_from_query(char *param, char **env) {

    regex_t regex;
    regmatch_t regmatch[2];

    int size = strlen(param) + 10;

    char *buffer = (char*)malloc(sizeof(char) * size);
    char *value = NULL;
    char *var = box_get_env_var("QUERY_STRING", env);

    snprintf(buffer, size, "%s=([^&]+)", param);

    if (0 != regcomp(&regex, buffer, REG_EXTENDED)) {
        printf("regcomp() failed\n");
        exit(EXIT_FAILURE);
    }

    if (regexec(&regex, var, 2, regmatch, 0) == 0) {
        value = box_get_regex_string(regmatch, var);
    }

    free(var);
    free(buffer);

    return value;
}

static char *box_get_regex_string(regmatch_t* reg, const char *string) {

    int size;
    char *match;

    size = reg[1].rm_eo - reg[1].rm_so;

    match = (char*)malloc(sizeof(char)*(size+1));

    strncpy(match, string + reg[1].rm_so, size);
    match[size] = '\0';

    return match;
}
