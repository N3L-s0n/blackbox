#ifndef BOX_HTML_H
#define BOX_HTML_H

#include "../mem/box_ntree.h"
#include "../mem/box_array.h"
#include "../mem/box_map.h"
#include "../utils/box_regex.h"

#include <stdio.h>

#define BOX_TAGS    0
#define BOX_CONTENT 1
#define BOX_DUMMY   2
#define BOX_HIDDEN  3

#define CHECK_LOGGED 21
#define CHECK_VISIT  22
#define CHECK_NOTHING 0

#define USER_LOGGED 21
#define USER_VISIT  22

typedef struct box_element {

    int type;

} box_element;

typedef struct box_el_content {

    box_element super;

    char *content;

} box_el_content;

typedef struct box_el_tags {

    box_element super;

    int check_user;

    char *open_tag;
    char *close_tag;

} box_el_tags;

typedef struct box_document {

    box_ntree     *ntree;
    int *login;

    box_map_array *class_map;

} box_document;

extern box_element *box_new_element_tags(char *open, char *close, int check);
extern box_element *box_new_element_content(char *content);
extern void *box_copy_element(void *element);

extern box_document *box_new_document(int *login);

extern void  box_destroy_element(void *element);
extern void box_destroy_document(box_document *document);

extern box_element *box_document_add_tag(box_document *document, char *open, char *close, int check);
extern box_element *box_document_add_content(box_document *document, char *content);

extern box_element *box_document_get_last_element(box_document *document);
extern box_element *box_document_set_close_tag(box_element *element, char *close_tag);

extern void box_document_map_classes(box_document *document);

extern void box_document_element_up(box_document *document);

extern void box_document_print(box_document *document);

extern void box_document_replicate(box_document *document, char *key, int index, int n);

extern void box_document_set_variables(box_document *document, char *key, char *variables, int index);

extern void box_document_hide(box_document *document, char *key, int index);

extern int box_document_get_class_n(box_document *document, char *key);

#endif
