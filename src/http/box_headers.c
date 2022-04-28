#include "box_headers.h"

static char *box_content_type_values[] = {

    /* BOX_TYPE_TEXT_HTML */
    "text/html",

    /* BOX_TYPE_TEXT_PLAIN */
    "text/plain",

    /* BOX_TYPE_CHARSET_UTF */
    "charset=utf-8"
};

extern void box_print_content_type( int* values, int count ){
    
    printf( "%s: ", BOX_CONTENT_TYPE );

    for( int i=0; i<count; ++i){
        printf("%s; ", box_content_type_values[values[i]]); 
    }

    printf( "%s", BOX_HEADER_END );
}
