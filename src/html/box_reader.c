#include "box_reader.h"

/* declarations */
static void box_read_document_recursive(document doc, char *filename, int check);

static char *box_handle_tag(document doc, char *tmpline, int check);

static char *box_handle_content(document doc, char *tmpline);

static char *box_read_buffer(FILE *fp);

/* definitions */

extern document box_open_document(int *login) {

    document doc = box_new_document(login);
    return doc;
}

extern void box_read_document(document doc, char *filename) {

    box_read_document_recursive(doc, filename, CHECK_NOTHING);
    box_document_map_classes(doc);
}

static void box_read_document_recursive(document doc, char *filename, int check) {

    char    *line = NULL;
    char *tmpline = NULL;

    int check_logged = check;

    FILE *fp = fopen(filename, "r");

    if (fp == NULL) {
        fprintf(stderr, "Could not open file %s\n", filename);
        exit(1);
    }
    
    while ((line = box_read_buffer(fp)) != NULL) {

        tmpline = line;

        while (1) {

            if (box_check_regex_match(tmpline, COMPONENT) == MATCH) {

                char* file = box_get_regex_match(tmpline, COMPONENT);
                tmpline = box_move_regex_match(tmpline, AFTER_COMMENT);
                
                box_read_document_recursive(doc, file, check_logged);
                free(file);
            }
            
            if (box_check_regex_match(tmpline, IF_LOGGED) == MATCH) {
                tmpline = box_move_regex_match(tmpline, AFTER_LOGGED);
                check_logged = CHECK_LOGGED;
            }

            if (box_check_regex_match(tmpline, IF_NOT_LOGGED) == MATCH) {
                tmpline = box_move_regex_match(tmpline, AFTER_N_LOGGED);
                check_logged = CHECK_VISIT;
            }
            
            if (box_check_regex_match(tmpline, GENERIC_TAG) == MATCH) {
                tmpline = box_handle_tag(doc, tmpline, check_logged);
                check_logged = CHECK_NOTHING;
                continue;
            }

            if(box_check_regex_match(tmpline, EMPTY_STRING) != MATCH) {
                box_handle_content(doc, tmpline);
            }

            break;
        }

        if (line != NULL) free(line);
    }
}

static char *box_read_buffer(FILE *fp) {

    char *line   = NULL;
    char *buffer = NULL;

    size_t len;
    size_t size;
    ssize_t read;

    int new_size = 0;
    
    while ((read = getline( &line, &len, fp)) != -1) {

        if (buffer == NULL) {
            new_size = read;
            buffer = (char*) calloc(new_size+1, sizeof(char));
        }
        else {
            new_size = read + strlen(buffer);
            buffer = (char*)realloc(buffer, sizeof(char) * (new_size+1));
        }

        strncat(buffer, line, read);
        buffer[new_size] = '\0';

        if (box_check_regex_match(buffer, ENDS_WITH_TAG) == MATCH) break;
    }
    
    if (line != NULL) free(line);

    return buffer;
    
}

static char *box_handle_content(document doc, char *tmpline) {
    
    box_document_add_content(doc, tmpline);
    box_document_element_up(doc);
}

static char *box_handle_tag(document doc, char *tmpline, int check) {

    char *match;
    char *body;

    match = box_get_regex_match(tmpline, GENERIC_TAG);
    body  = box_get_regex_match(tmpline, TAG_BODY);

    if(box_check_regex_match(body, EMPTY_STRING) != MATCH) {
            box_handle_content(doc, body);
    }

    if (box_check_regex_match(match, VOID_TAG) == MATCH || box_check_regex_match(match, DOCTYPE) == MATCH) {       // VOID TAG

        element el = box_document_add_tag(doc, match, NULL, check);

        box_document_element_up(doc);
    }
    else if (box_check_regex_match(match, END_TAG) == MATCH) {   // END TAG
        
        element el = box_document_get_last_element(doc);
        box_document_set_close_tag(el, match);
       
        box_document_element_up(doc);
    }
    else {                                                      // START TAG
        element el = box_document_add_tag(doc, match, NULL, check);
    }

    if (match != NULL) free(match); 
    if (body != NULL) free(body);

    return box_move_regex_match(tmpline, AFTER_TAG);
}
