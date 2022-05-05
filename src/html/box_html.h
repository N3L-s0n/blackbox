#ifndef BOX_HTML_H
#define BOX_HTML_H

#include "box_tags.h"

#include "../mem/box_ntree.h"
#include "../mem/box_array.h"

#include <stdio.h>

typedef struct box_html_element {

    int html_id;
    int html_tag;
    int html_class;

    char *content;
    char *opening_tag;
    char *closing_tag;

} box_html_element;

typedef struct box_html_tree {

    box_ntree *ntree;
    box_array *classes;

} box_html_tree;

extern box_html_element *box_new_html_element(void);

extern box_html_element *box_html_get_last_element(box_html_tree *tree);

extern void  box_destroy_html_element(void *element);

extern box_html_tree *box_new_html_tree(void);

extern box_html_element *box_html_tree_add_node(box_html_tree *tree);

extern void box_destroy_html_tree(box_html_tree *tree);

extern void box_html_element_up(box_html_tree *tree);

extern void box_html_print_document(box_html_tree *tree);

extern void box_html_print_by_tag(box_html_tree *tree, char *tag);

extern void box_html_print_by_tag_excluded(box_html_tree *tree, char *tag);

/* html_id */
extern int   box_html_get_html_id(box_html_element *element);
extern void  box_html_set_html_id(box_html_element *element, int value);


/* html_tag */
extern int   box_html_get_html_tag(box_html_element *element);
extern void  box_html_set_html_tag(box_html_element *element, int value);


/* html_class */
extern int   box_html_get_html_class(box_html_element *element);
extern void  box_html_set_html_class(box_html_element *element, int value);


/* content */
extern char *box_html_get_content(box_html_element *element);
extern void  box_html_set_content(box_html_element *element, char *value);


/* openening_tag */
extern char *box_html_get_opening_tag(box_html_element *element);
extern void  box_html_set_opening_tag(box_html_element *element, char *value);


/* closing_tag */
extern char *box_html_get_closing_tag(box_html_element *element);
extern void  box_html_set_closing_tag(box_html_element *element, char *value);



#endif
