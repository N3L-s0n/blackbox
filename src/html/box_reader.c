#include "box_reader.h"

/* declarations */

static void box_set_tag(box_file file, char *line);

static char *box_handle_tag(box_file file, char *tmpline);

static char *box_handle_element(box_file file, char *tmpline);

/* definitions */

extern box_file box_read_file(char *filename) {

    ssize_t read;
     size_t len;

    char    *line = NULL;
    char *tmpline = NULL;

    FILE *fp = fopen(filename, "r");

    if (fp == NULL) {
        fprintf(stderr, "Could not open file %s\n", filename);
        exit(1);
    }
    
    box_file file = box_new_html_tree();

    while ((read = getline( &line, &len, fp)) != -1) {

        tmpline = line;

        while (1) {
            
            int result = box_check_regex_match(tmpline, GENERIC_TAG);

            if (result == MATCH) {
                tmpline = box_handle_tag(file, tmpline);
                continue;
            }

            if(box_check_regex_match(tmpline, EMPTY_STRING) != MATCH) {
                box_handle_element(file, box_copy_string(tmpline));
            }

            break;
        }
    }

    if (line != NULL) free(line);

    return file;
}

extern void box_destroy_file(box_file file) {

    box_destroy_html_tree(file);
}

static char *box_handle_element(box_file file, char *tmpline) {
    
    element el = box_html_tree_add_node(file);
    box_html_set_opening_tag(el, tmpline); // Opening tag works as body too

    box_html_element_up(file);
}

static char *box_handle_tag(box_file file, char *tmpline) {

    char *match;
    char *body;

    match = box_get_regex_match(tmpline, GENERIC_TAG);
    body  = box_get_regex_match(tmpline, TAG_BODY);

    if (box_check_regex_match(match, VOID_TAG) == MATCH) {       // VOID TAG
                                                //
        element el = box_html_tree_add_node(file);
        box_html_set_opening_tag(el, match);

        box_set_tag(file, match);
        box_html_element_up(file);

        if (body != NULL) free(body);
    }
    else if (box_check_regex_match(match, END_TAG) == MATCH) {   // END TAG
        
        element el = box_html_get_last_element(file);
        box_html_set_closing_tag(el, match);
       
        box_handle_element(file, body);
        box_html_element_up(file);
    }
    else {                                                      // START TAG
        
        element el = box_html_tree_add_node(file);
        box_html_set_opening_tag(el, match);

        box_set_tag(file, match);

        if (body != NULL) free(body); 
    }
    
    return box_move_regex_match(tmpline, AFTER_TAG);
}

static void box_set_tag(box_file file, char *line) {
    
    char *string = box_get_regex_match(line, TAG_NAME);

    if (string != NULL) {
        
        box_html_set_html_tag(box_html_get_last_element(file), box_html_tag_id(string));
        free(string);
    }

}
