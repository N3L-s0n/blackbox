#include "box_headers.h"

typedef void (*box_header_handler)(void*, unsigned int);

struct box_headers {

    struct box_header_node  *root;   
    struct box_header_node  *last;   
    int                     count;

};

typedef struct box_header_node box_header_node;

struct box_header_node {

   box_header_handler   handler;
   void                 *values;
   unsigned int          count;

   struct box_header_node   *next;
};

static char *box_response_status[] = {

    /* 200 OK */
    "Status:200 OK",

    /* 201 CREATED */
    "Status:201 Created",

    /* 202 ACCEPTED */
    "Status:202 Accepted",

    /* 302 Found */
    "Status:302 Found"

    /* 308 Permantent Redirect */
    "Status:308 Permanent Redirect"
};

static char *box_content_type_values[] = {

    /* BOX_TYPE_TEXT_HTML */
    "text/html",

    /* BOX_TYPE_TEXT_PLAIN */
    "text/plain",

    /* BOX_TYPE_CHARSET_UTF */
    "charset=utf-8"

};


static void box_response_status_handler(void *values, unsigned int count);

static void box_content_type_handler(void *values, unsigned int count);

static void box_location_handler(void *values, unsigned int count);

static void box_cookie_handler(void *values, unsigned int count);


static box_header_node* box_add_header(box_headers *headers, box_header_handler handler, unsigned int values_count);

extern box_headers* box_new_headers(void) {
    
    box_headers *headers = (box_headers*)malloc(sizeof(box_headers));

    /* ALL HEADERS SHOULD HAVE A RESPONSE STATUS */
    box_header_node *node = box_add_header(headers, &box_response_status_handler, 1);
    ((uint8_t*) node->values)[0] = BOX200;

    return headers;
}

static box_header_node* box_add_header(box_headers *headers, box_header_handler handler, unsigned int values_count) {
    //crear nod
    box_header_node *node = (box_header_node*)malloc(sizeof(box_header_node));
    // handler funcion imprimir
    *node = (box_header_node) {
        .handler = handler,
        .values = (void*)calloc(values_count, sizeof(uint8_t)),
        .count = values_count,
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

/* REPLACE RESPONSE STATUS */
extern void box_header_add_response_status(box_headers *headers, uint8_t value) {
    
    box_header_node *node = headers->root;

    ((uint8_t*) node->values)[0] = value;

}


extern void box_header_add_content_type(box_headers *headers, unsigned int count, va_list args) {
   
    box_header_node *node = box_add_header(headers, &box_content_type_handler, count); 

    for (int i = 0; i < count; ++i) {
        ((uint8_t*) node->values)[i] = (uint8_t) va_arg(args, int); // should be checked
    }
}

extern void box_header_add_location(box_headers *headers, const char *url) {
    
    if (url != NULL) {
        box_header_node *node = box_add_header(headers, &box_location_handler, strlen(url)+1);

        strncpy((char *)node->values, url, strlen(url));
    }
}

extern void box_header_add_cookie(box_headers *headers, const char *cookie) {
    
    if (cookie != NULL) {
        box_header_node *node = box_add_header(headers, &box_cookie_handler, strlen(cookie)+1);

        strncpy((char *)node->values, cookie, strlen(cookie));
    }
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

/* HEADERS HANDLERS */
//values = vector de string , primero cookie, segundo expires....
static void box_content_type_handler(void *values, unsigned int count) {
    
    printf( "%s: ", BOX_CONTENT_TYPE );

    for (int i=0; i<count; ++i) {
        printf("%s%s", box_content_type_values[((uint8_t*) values)[i]], (i+1 == count) ? "" : "; "); 
    }
}

static void box_response_status_handler(void *values, unsigned int count) {
    
    if (count == 1) {
        printf("%s",  box_response_status[((uint8_t*) values)[0]]);
    }
}

static void box_location_handler(void *values, unsigned int count) {

    if (count > 0) {
        printf( "%s: %s", BOX_LOCATION, (char *)values);
    }
}

static void box_cookie_handler(void *values, unsigned int count) {

    if (count > 0) {
        printf( "%s: %s", BOX_COOKIE, (char *)values);
    }
}
