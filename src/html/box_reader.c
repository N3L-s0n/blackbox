#include "box_reader.h"

/* declarations */

static char *box_handle_tag(document doc, char *tmpline);

static char *box_handle_content(document doc, char *tmpline);

static char *box_read_buffer(FILE *fp);

/* definitions */

extern document box_read_document(char *filename) {

    char    *line = NULL;
    char *tmpline = NULL;

    FILE *fp = fopen(filename, "r");

    if (fp == NULL) {
        fprintf(stderr, "Could not open file %s\n", filename);
        exit(1);
    }
    
    document doc = box_new_document();

    while ((line = box_read_buffer(fp)) != NULL) {

        tmpline = line;

        while (1) {
            
            if (box_check_regex_match(tmpline, GENERIC_TAG) == MATCH) {
                tmpline = box_handle_tag(doc, tmpline);
                continue;
            }

            if(box_check_regex_match(tmpline, EMPTY_STRING) != MATCH) {
                box_handle_content(doc, tmpline);
            }

            break;
        }

        if (line != NULL) free(line);
    }

    box_document_map_classes(doc);
    return doc;
}

static char *box_read_buffer(FILE *fp) {

    char *line   = NULL;
    char *buffer = NULL;

    size_t len;
    size_t size;
    ssize_t read;
    
    while ((read = getline( &line, &len, fp)) != -1) {

        if (buffer == NULL) {
            buffer = (char*) calloc(read+1, sizeof(char));
        }
        else {
            buffer = (char*)realloc(buffer, sizeof(char) * (read + strlen(buffer)));
        }

        strncat(buffer, line, read);

        if (box_check_regex_match(buffer, ENDS_WITH_TAG) == MATCH) break;
    }
    
    if (line != NULL) free(line);

    return buffer;
    
}

static char *box_handle_content(document doc, char *tmpline) {
    
    box_document_add_content(doc, tmpline);
    box_document_element_up(doc);
}

static char *box_handle_tag(document doc, char *tmpline) {

    char *match;
    char *body;

    match = box_get_regex_match(tmpline, GENERIC_TAG);
    body  = box_get_regex_match(tmpline, TAG_BODY);

    if (box_check_regex_match(match, VOID_TAG) == MATCH) {       // VOID TAG
                                                //
        element el = box_document_add_tag(doc, match, NULL);

        box_document_element_up(doc);
    }
    else if (box_check_regex_match(match, END_TAG) == MATCH) {   // END TAG
        
        element el = box_document_get_last_element(doc);
        box_document_set_close_tag(el, match);
       
        if(box_check_regex_match(body, EMPTY_STRING) != MATCH) {
            box_handle_content(doc, body);
        }
        box_document_element_up(doc);
    }
    else {                                                      // START TAG
        
        element el = box_document_add_tag(doc, match, NULL);
    }

    if (match != NULL) free(match); 
    if (body != NULL) free(body);

    return box_move_regex_match(tmpline, AFTER_TAG);
}
