#include "box_http.h"

typedef struct box_http {
    
    box_headers *headers;
    box_file    html;

    char        **env;

    char        *query_string;
    char        *post_body;

} box_http;


/* HTTP STRUCT */
/* creates new http struct & sets 200 OK response */
extern box_http *box_new_http(char *filename, char **env) {
    
    box_http *http = (box_http*)malloc(1 * sizeof(box_http));

    *http = (box_http) {
        .headers = box_new_headers(),
        .query_string = NULL,
        .post_body = NULL,
        .html = NULL,
        .env = env
    };

    if (filename != NULL) http->html = box_read_file(filename);

    return http;
}

/* destroy http struct and all related data */
extern void  box_destroy_http(box_http *http) {

    if (http != NULL) {

        if (http->headers != NULL) box_destroy_headers(http->headers);

        if (http->html != NULL) box_destroy_html_tree(http->html);

        if (http->query_string != NULL) free(http->query_string);

        if (http->post_body != NULL) free(http->post_body);

        free(http);
    }
}

/* opens a html file */
extern void  box_http_file(box_http *http, char *filename) {

    if (http->html == NULL && filename != NULL) http->html = box_read_file(filename); 
}

/* sets environment variables */
extern void  box_http_env(box_http *http, char  **env) {

    http->env = env;
}

extern void box_http_send(box_http *http) {

    box_send_headers(http);
    box_send_html(http);
}



/* HEADERS RELATED */
/* sets response, box_headers.h has response code enum */
extern void box_http_response(box_http *http, uint8_t value) {

    box_header_add_response_status(http->headers, value);

}

/* sets type content header & values, box_headers.h has available values enum */
extern void box_http_content (box_http *http, unsigned int count, ...) {

    va_list args;
    va_start(args, count);

    box_header_add_content_type(http->headers, count, args);
    
    va_end(args);
}

/* sets redirect 302 found & location */
extern void box_http_redirect(box_http *http, char *url) {

    box_header_add_response_status(http->headers, BOX302);
    box_header_add_location(http->headers, url);
}

/* sets location header, only use it with 30x & 201 */
extern void box_http_location(box_http *http, char *url) {

    box_header_add_location(http->headers, url);
}

/* send headers */
extern void box_send_headers(box_http *http) {

    box_print_headers(http->headers);
}

extern void box_send_html(box_http *http) {

    if (http->html != NULL) {

        box_html_print_document(http->html);
    }
}



/* CLIENT INPUT */
extern char *box_get_env_var(char *varname, char **env) {

    char *var = NULL;

    int size = strlen(varname) + 10;
    char *buffer = (char*)malloc(sizeof(char) * size);

    snprintf(buffer, size, "%s=(.*)", varname);

    while(*env) {

        if ((var = box_get_regex_match(*env, buffer)) != NULL) break;

        env++;
    }

    free(buffer);

    return var;
}

extern char *box_get_value_from_query(char *param, char **env) {

    int size = strlen(param) + 10;

    char *buffer = (char*)malloc(sizeof(char) * size);
    char *value = NULL;

    char *var = box_get_env_var("QUERY_STRING", env);

    if(var != NULL) {

        snprintf(buffer, size, "%s=([^&]+)", param);

        value = box_get_regex_match(var, buffer);

        free(var);
    }

    free(buffer);

    return value;
}

