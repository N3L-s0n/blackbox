#ifndef BOX_HTTP_H
#define BOX_HTTP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>

#include "box_headers.h"
#include "../html/box_html.h"
#include "../html/box_reader.h"

#include "../utils/box_regex.h"

typedef struct box_http box_http;


/* HTTP STRUCT */
/* creates new http struct & sets 200 OK response */
extern box_http *box_new_http(char *filename, char **env);

/* destroy http struct and all related data */
extern void  box_destroy_http(box_http *http);

/* opens a html file */
extern void  box_http_file(box_http *http, char *filename);

/* sets environment variables */
extern void  box_http_env(box_http *http, char  **env);

/* sends headers & html if available */
extern void box_http_send(box_http *http);

/* returns 1 if post method */
extern int  box_http_has_post(box_http *http);

/* returns 1 if get method with query string */
extern int  box_http_has_query(box_http *http);


/* HEADERS RELATED */
/* sets response, box_headers.h has response code enum */
extern void box_http_response(box_http *http, uint8_t value);

/* sets type content header & values, box_headers.h has available values enum */
extern void box_http_content (box_http *http, unsigned int count, ...);

/* sets redirect 302 found & location */
extern void box_http_redirect(box_http *http, char *url);

/* sets location header, only use it with 30x & 201 */
extern void box_http_location(box_http *http, char *url);

/* send headers */
extern void box_send_headers(box_http *http);

/* send html file */
extern void box_send_html(box_http *http);


/* CLIENT INPUT */
extern char *box_query_param(box_http *http, char *param);

extern char *box_post_param(box_http *http, char *param);

/* HTML OPERATIONS */
extern void *box_replicate_class(box_http *http, char *html_class, int index, int n);

extern void *box_replicate_id(box_http *http, char *html_id, int index, int n);

extern void box_set_class_variables(box_http *http, char *html_class, char *variables, int index);

extern void box_set_id_variables(box_http *http, char *html_id, char *variables, int index);

extern int  box_class_n_instances(box_http *http, char *html_class);

#endif
