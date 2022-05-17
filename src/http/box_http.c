#include "box_http.h"

typedef struct box_http {
    
    box_headers *headers;
    document    html;

    char        **env;

    char        *query_string;
    char        *post_body;

} box_http;

static int  box_read_post_body(box_http *http);

static int  box_read_query_string(box_http *http);

static char *box_get_env_var(box_http *http, char *varname);

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

    if (filename != NULL) http->html = box_read_document(filename);

    box_read_query_string(http);
    box_read_post_body(http);

    return http;
}

/* destroy http struct and all related data */
extern void  box_destroy_http(box_http *http) {

    if (http != NULL) {

        if (http->headers != NULL) box_destroy_headers(http->headers);

        if (http->html != NULL) box_destroy_document(http->html);

        if (http->query_string != NULL) free(http->query_string);

        if (http->post_body != NULL) free(http->post_body);

        free(http);
    }
}

/* opens a html file */
extern void  box_http_file(box_http *http, char *filename) {

    if (http->html == NULL && filename != NULL) http->html = box_read_document(filename); 
}

/* sets environment variables */
extern void  box_http_env(box_http *http, char  **env) {

    http->env = env;
}

extern void box_http_send(box_http *http) {

    box_send_headers(http);
    box_send_html(http);
}

/* returns 1 if post method */
extern int  box_http_has_post(box_http *http) {

    if (http->post_body != NULL) return 1;

    return box_read_post_body(http); // try to read it again if env was not set
}

/* returns 1 if get query string */
extern int  box_http_has_query(box_http *http) {

    if (http->query_string != NULL) return 1;

    return box_read_query_string(http);
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

        box_document_print(http->html);
    }
}


/* CLIENT INPUT */
static int  box_read_post_body(box_http *http) {

    char *cont_len = box_get_env_var(http, "CONTENT_LENGTH");

    if (cont_len != NULL) {

        int len = atoi(cont_len);

        char *buffer = (char*)calloc(len+1, sizeof(char));
        read(0, buffer, len);

        http->post_body = buffer;

        free(cont_len);
        return 1;
    }

    return 0;
}

static int  box_read_query_string(box_http *http) {

    char *query = box_get_env_var(http, "QUERY_STRING");

    if (query != NULL) {
        http->query_string = query;

        return 1;
    }

    return 0;
}

static char *box_get_env_var(box_http *http, char *varname) {

    char *var = NULL;

    if (http->env != NULL) {

        char **env = http->env;

        int size = strlen(varname) + 10;
        char *buffer = (char*)malloc(sizeof(char) * size);

        snprintf(buffer, size, "%s=(.*)", varname);

        while(*env) {

            if ((var = box_get_regex_match(*env, buffer)) != NULL) break;

            env++;
        }

        free(buffer);
    }

    return var;
}

extern char *box_post_param(box_http *http, char *param) {

    char *value = NULL;

    if (http->post_body != NULL) { 

        int size = strlen(param) + 10;
        char *buffer = (char*)calloc(size+1, sizeof(char));

        snprintf(buffer, size, "%s=([^&]+)", param);

        value = box_get_regex_match(http->post_body, buffer);

        free(buffer);
    }

    return value;
}

extern char *box_query_param(box_http *http, char *param) {

    char *value = NULL;

    if (http->query_string != NULL) { 

        int size = strlen(param) + 10;
        char *buffer = (char*)calloc(size+1, sizeof(char));

        snprintf(buffer, size, "%s=([^&]+)", param);

        value = box_get_regex_match(http->query_string, buffer);

        free(buffer);
    }

    return value;
}

/* HTML OPERATIONS */
extern void *box_replicate_class(box_http *http, char *html_class, int index, int n) {
    
    box_document_replicate(http->html, BOX_CLASS, html_class, index, n);
}

extern void *box_replicate_id(box_http *http, char *html_id, int index, int n) {
    
    box_document_replicate(http->html, BOX_ID, html_id, index, n);
}


extern void box_set_class_variables(box_http *http, char *html_class, char *variables, int index) {
    box_document_set_variables(http->html, BOX_CLASS, html_class, variables, index);
}

extern void box_set_id_variables(box_http *http, char *html_id, char *variables, int index) {
    box_document_set_variables(http->html, BOX_ID, html_id, variables, index);
}

extern int   box_class_n_instances(box_http *http, char *html_class) {
    
    return box_document_get_class_n(http->html, html_class);
}


