#ifndef BOX_HTML_H
#define BOX_HTML_H

#include "box_tags.h"

#include "../mem/box_ntree.h"
#include "../mem/box_array.h"
#include "../mem/box_map.h"
#include "../utils/box_regex.h"

#include <stdio.h>

#define BOX_TAGS    0
#define BOX_CONTENT 1

typedef struct box_element {

    int type;

} box_element;

typedef struct box_el_content {

    box_element super;

    char *content;

} box_el_content;

typedef struct box_el_tags {

    box_element super;

    int tag;

    char *open_tag;
    char *close_tag;

} box_el_tags;

typedef struct box_document {

    box_ntree     *ntree;

    box_map_array *id_map;
    box_map_array *class_map;

} box_document;

extern box_element *box_new_element_tags(char *open, char *close);
extern box_element *box_new_element_content(char *content);
extern box_document *box_new_document(void);

extern void  box_destroy_element(void *element);
extern void box_destroy_document(box_document *document);

extern box_element *box_document_add_tag(box_document *document, char *open, char *close);
extern box_element *box_document_add_content(box_document *document, char *content);

extern box_element *box_document_get_last_element(box_document *document);
extern box_element *box_document_set_close_tag(box_element *element, char *close_tag);

extern void box_document_element_up(box_document *document);

extern void box_document_print(box_document *document);

extern void box_document_print_by_tag(box_document *document, char *tag);

#endif
