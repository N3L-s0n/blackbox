#ifndef BOX_HEADERS_H
#define BOX_HEADERS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

/* HTTP Headers*/
#define BOX_CONTENT_TYPE "Content-Type"

typedef struct box_headers box_headers;

#define BOX_HEADER_END  "\r\n"

/* HTTP Content-Type values */
typedef enum {
    
    TEXT_HTML = 0,
    TEXT_PLAIN,
    CHARSET_UTF_8
    
} box_type_values;

extern box_headers* box_new_headers(void);

extern void box_print_headers(box_headers *headers);

extern void box_destroy_headers(box_headers *headers);

extern void box_header_add_content_type(box_headers *headers, unsigned int *values, unsigned int count);

extern char *box_get_env_var(char *varname, char **env);

extern char *box_get_value_from_query(char *param, char **env);

#endif
