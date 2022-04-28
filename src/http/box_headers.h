#ifndef BOX_HEADERS_H
#define BOX_HEADERS_H

#include <stdio.h>

/* HTTP Headers*/
#define BOX_CONTENT_TYPE "Content-Type"

#define BOX_HEADER_END "\r\n"

/* HTTP Content-Type values */
#define BOX_TYPE_TEXT_HTML   0
#define BOX_TYPE_TEXT_PLAIN  1
#define BOX_TYPE_CHARSET_UTF 2

extern void box_print_content_type( int* values, int count );

#endif
