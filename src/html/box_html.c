#include "box_html.h"

/* static declarations */

static  int box_html_print_if_tag(box_ntree_node *node, void *data);

static  int box_html_print_if_tag_excluded(box_ntree_node *node, void *data);

static  int box_html_print_tag_excluded(box_ntree_node *node, void *data);

static  int box_html_print_opening_tag(box_ntree_node *node, void *data);

static void box_html_print_closing_tag(box_ntree_node *node, void *data);

static void box_html_print_closing_tag_excluded(box_ntree_node *node, void *data);


/* definitions */

extern box_html_element *box_new_html_element(void){

    box_html_element *element = (box_html_element *)malloc(sizeof(box_html_element));

    element->html_id = -1;
    element->html_tag = -1;
    element->html_class = -1;

    element->content = NULL;
    element->opening_tag = NULL;
    element->closing_tag = NULL;

    return element;
}

extern box_html_element *box_html_get_last_element(box_html_tree *tree){

    return (box_html_element *) box_worker_get_value(tree->ntree);

}

extern void  box_destroy_html_element(void *element){

    box_html_element *el = (box_html_element *) element;

    if (el != NULL) { 

        if (el->content != NULL) {
            free(el->content);
        }
        
        if (el->opening_tag != NULL) {
            free(el->opening_tag);
        }

        if (el->closing_tag != NULL) {
            free(el->closing_tag);
        }

        free(el);
    }
}

extern box_html_tree *box_new_html_tree(void){

    box_html_tree *tree = (box_html_tree *)malloc(sizeof(box_html_tree));

    box_ntree *ntree = box_new_ntree(10);

    tree->ntree   = ntree;
    tree->classes = NULL;

    return tree;
}

extern box_html_element *box_html_tree_add_node(box_html_tree *tree) {
    
    box_html_element *element = box_new_html_element();
    box_worker_set_value(box_add_ntree_node(tree->ntree), element);

    return element;
}

extern void box_html_element_up(box_html_tree *tree) {
    
   box_worker_up(tree->ntree); 
}

extern void box_destroy_html_tree(box_html_tree *tree) {

    if (tree->ntree != NULL) {
        box_destroy_ntree(tree->ntree, &box_destroy_html_element);
    }

}

extern void box_html_print_document(box_html_tree *tree) {
    
    box_traverse_ntree(tree->ntree, &box_html_print_opening_tag, &box_html_print_closing_tag, NULL);
}

extern void box_html_print_by_tag(box_html_tree *tree, char *tag) {

    if (tag != NULL) {
    
        int id = box_html_tag_id(tag);

        box_traverse_ntree(tree->ntree, &box_html_print_if_tag, NULL, (void *)&id);

    }
}

extern void box_html_print_by_tag_excluded(box_html_tree *tree, char *tag) {

    if (tag != NULL) {
    
        int id = box_html_tag_id(tag);

        box_traverse_ntree(tree->ntree, &box_html_print_if_tag_excluded, NULL, (void *)&id);

    }
}

static  int box_html_print_if_tag(box_ntree_node *node, void *data) { 

    int res = 0;
    int id = *(int*)data;

    box_html_element *element = (box_html_element *)box_ntree_node_get_value(node);

    if (element->opening_tag != NULL && element->html_tag == id) {
        res = 1;

        box_traverse_nodes(node, &box_html_print_opening_tag, &box_html_print_closing_tag, NULL);
    }
    
    return res;
}

static  int box_html_print_if_tag_excluded(box_ntree_node *node, void *data) { 

    int res = 0;
    int id = *(int*)data;

    box_html_element *element = (box_html_element *)box_ntree_node_get_value(node);

    if (element->opening_tag != NULL && element->html_tag == id) {
        res = 1;

        box_traverse_nodes(node, &box_html_print_tag_excluded, &box_html_print_closing_tag_excluded, data);
    }
    
    return res;
}

static  int box_html_print_tag_excluded(box_ntree_node *node, void *data) {

    int id = *(int*)data;

    box_html_element *element = (box_html_element *)box_ntree_node_get_value(node);

    if (element->opening_tag != NULL && element->html_tag != id) {
        printf("%s\n", element->opening_tag); 
    }
    
    return 0;
}

static  int box_html_print_opening_tag(box_ntree_node *node, void *data) {

    box_html_element *element = (box_html_element *)box_ntree_node_get_value(node);

    if (element->opening_tag != NULL) {
        printf("%s\n", element->opening_tag); 
    }
    
    return 0;
}

static void box_html_print_closing_tag(box_ntree_node *node, void *data) {

    box_html_element *element = (box_html_element *)box_ntree_node_get_value(node);

    if (element->closing_tag != NULL) {
        printf("%s\n", element->closing_tag); 
    }
}

static void box_html_print_closing_tag_excluded(box_ntree_node *node, void *data) {

    int id = *(int*)data;

    box_html_element *element = (box_html_element *)box_ntree_node_get_value(node);

    if (element->closing_tag != NULL && element->html_tag != id) {
        printf("%s\n", element->closing_tag); 
    }
}

/* html_id */
extern int   box_html_get_html_id(box_html_element *element){

    int value = -1;

    if (element != NULL) {
        value = element->html_id;
    }

    return value;
}
extern void  box_html_set_html_id(box_html_element *element, int value){

    if (element != NULL) {
        element->html_id = value;
    }
}


/* html_tag */
extern int   box_html_get_html_tag(box_html_element *element){

    int value = -1;

    if (element != NULL) {
        value = element->html_tag;
    }

    return value;

}
extern void  box_html_set_html_tag(box_html_element *element, int value){

    if (element != NULL) {
        element->html_tag = value;
    }
}


/* html_class */
extern int   box_html_get_html_class(box_html_element *element){

    int value = -1;

    if (element != NULL) {
        value = element->html_class;
    }

    return value;

}
extern void  box_html_set_html_class(box_html_element *element, int value){

    if (element != NULL) {
        element->html_class = value;
    }
}


/* content */
extern char *box_html_get_content(box_html_element *element){

    char *value = NULL;

    if (element != NULL) {
        value = element->content;
    }

    return value;

}
extern void  box_html_set_content(box_html_element *element, char *value){

    if (element != NULL) {
        element->content = value;
    }
}


/* openening_tag */
extern char *box_html_get_opening_tag(box_html_element *element){

    char *value = NULL;

    if (element != NULL) {
        value = element->opening_tag;
    }

    return value;

}
extern void  box_html_set_opening_tag(box_html_element *element, char *value){

    if (element != NULL) {
        element->opening_tag = value;
    }
}


/* closing_tag */
extern char *box_html_get_closing_tag(box_html_element *element){

    char *value = NULL;

    if (element != NULL) {
        value = element->closing_tag;
    }

    return value;

}
extern void  box_html_set_closing_tag(box_html_element *element, char *value){

    if (element != NULL) {
        element->closing_tag = value;
    }
}



