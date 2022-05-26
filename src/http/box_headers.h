#ifndef BOX_HEADERS_H
#define BOX_HEADERS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdint.h>

/* HTTP Headers*/
#define BOX_CONTENT_TYPE    "Content-Type"
#define BOX_LOCATION        "Location"
#define BOX_SET_COOKIE      "Set-Cookie"
#define BOX_COOKIE          "Cookie"


typedef struct box_headers box_headers;

#define BOX_HEADER_END  "\r\n"

#define THIS_PAGE argv[0]


typedef enum {
    
    BOX200 = 0,
    BOX201, // typical POST response
    BOX202,

    BOX302,
    BOX308

} box_responses;


/* HTTP Content-Type values */
typedef enum {
    
    TEXT_HTML = 0,
    TEXT_PLAIN,
    CHARSET_UTF_8
    
} box_type_values;

extern box_headers* box_new_headers(void);
extern void box_destroy_headers(box_headers *headers);

extern void box_print_headers(box_headers *headers);

/* Headers modifiers */
extern void box_header_add_response_status(box_headers *headers, uint8_t value);

extern void box_header_add_content_type(box_headers *headers, unsigned int count, va_list args);

extern void box_header_add_cookie(box_headers *headers,  const char * cookie);


/* url can be relative or absolute */
extern void box_header_add_location(box_headers *headers, const char *url);

#endif
