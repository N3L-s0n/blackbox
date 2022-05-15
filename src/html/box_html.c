#include "box_html.h"

/* static declarations */

static  int box_print_if_tag(box_ntree_node *node, void *data);

static  int box_print_open_tag(box_ntree_node *node, void *data);

static void box_print_close_tag(box_ntree_node *node, void *data);

static void box_set_tag(box_el_tags *tag);


/* definitions */
extern box_element *box_new_element_tags(char *open, char *close){

    box_el_tags *element = (box_el_tags *)malloc(sizeof(box_el_tags));

    *element = (box_el_tags) {
        .super.type = BOX_TAGS,
        .open_tag   = box_copy_string(open),
        .close_tag  = box_copy_string(close)
    };

    return (box_element *) element;
}

extern box_element *box_new_element_content(char *content){

    box_el_content *element = (box_el_content *)malloc(sizeof(box_el_content));

    *element = (box_el_content) {
        .super.type = BOX_CONTENT,
        .content    = box_copy_string(content)
    };

    return (box_element *) element;
}

extern void  box_destroy_element(void *element){

    box_element *el = (box_element *) element;

    if (el != NULL & el->type == BOX_TAGS) {

        box_el_tags *tag = (box_el_tags *)el;

        if (tag->open_tag != NULL) free(tag->open_tag);
        if (tag->close_tag != NULL) free(tag->close_tag);

        free(tag);
    }
    else if (el != NULL & el->type == BOX_CONTENT) {

        box_el_content *cont = (box_el_content *)el;

        if (cont->content != NULL) free(cont->content);

        free(cont);
    }
    else {
        fprintf(stderr, "Trying to destroy not valid element\n");
    }
}

extern box_document *box_new_document(void){

    box_document *document = (box_document *)malloc(sizeof(box_document));

    document->ntree     = box_new_ntree(10);
    document->id_map    = box_new_map_array();
    document->class_map = box_new_map_array();

    return document;
}

extern void box_destroy_document(box_document *document) {

    if (document != NULL) {

        if (document->ntree != NULL) {
            box_destroy_ntree(document->ntree, &box_destroy_element);
        }
        if (document->id_map != NULL) {
            box_destroy_map_array(document->id_map);
        }
        if (document->class_map != NULL) {
            box_destroy_map_array(document->class_map);
        }

    }
}


extern box_element *box_document_add_tag(box_document *document, char *open, char *close) {
    
    box_element *element = box_new_element_tags(open, close);
    box_set_tag((box_el_tags*) element);
    box_worker_set_value(box_add_ntree_node(document->ntree), element);

    return element;
}

extern box_element *box_document_add_content(box_document *document, char *content) {
    
    box_element *element = box_new_element_content(content);
    box_worker_set_value(box_add_ntree_node(document->ntree), element);

    return element;
}


extern box_element *box_document_get_last_element(box_document *document) {

    return (box_element *) box_worker_get_value(document->ntree);

}

extern box_element *box_document_set_close_tag(box_element *element, char *close_tag) {
   
    if(element->type != BOX_TAGS) {

        fprintf(stderr, "Not an element tag\n");
    }
    else {
        box_el_tags *tag = (box_el_tags *)element;
        tag->close_tag = box_copy_string(close_tag);
    }

    return element;
}

extern void box_document_element_up(box_document *document) {
    
   box_worker_up(document->ntree); 
}

extern void box_document_print(box_document *document) {
    
    box_traverse_ntree(document->ntree, &box_print_open_tag, &box_print_close_tag, NULL);
}

extern void box_document_print_by_tag(box_document *document, char *tag) {

    if (tag != NULL) {
    
        int id = box_html_tag_id(tag);

        box_traverse_ntree(document->ntree, &box_print_if_tag, NULL, (void *)&id);

    }
}

static  int box_print_if_tag(box_ntree_node *node, void *data) { 

    int res = 0;
    int id = *(int*)data;

    box_element *element = (box_element *)box_ntree_node_get_value(node);

    if (element->type == BOX_TAGS) {
    
        box_el_tags *tag = (box_el_tags *)element;

        if (tag->open_tag != NULL && tag->tag == id) {

            res = 1;
            box_traverse_nodes(node, &box_print_open_tag, &box_print_close_tag, NULL);
        }

    }
    
    return res;
}

static  int box_print_open_tag(box_ntree_node *node, void *data) {

    box_element *element = (box_element *)box_ntree_node_get_value(node);

    if (element->type == BOX_CONTENT) {
        box_el_content *cont = (box_el_content *)element;
        printf("%s", cont->content);

        return 1; // No need to continue traversing nodes from content one
    }

    if (element->type == BOX_TAGS) {
        box_el_tags *tag = (box_el_tags *)element;
        printf("%s", tag->open_tag); 

        return 0;
    }
    
    return 1;
}

static void box_print_close_tag(box_ntree_node *node, void *data) {

    box_element *element = (box_element *)box_ntree_node_get_value(node);

    if (element->type == BOX_TAGS) {

        box_el_tags *tag = (box_el_tags *)element;

        // VOID TAGS don't have close tag
        if (tag->close_tag != NULL) printf("%s", tag->close_tag); 
    }
}

static void box_set_tag(box_el_tags *tag) {
    
    char *string = box_get_regex_match(tag->open_tag, TAG_NAME);

    if (string != NULL) {
        tag->tag = box_html_tag_id(string);
        free(string); 
    }
}
