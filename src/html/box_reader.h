#ifndef BOX_READER_H
#define BOX_READER_H

#include <stdio.h>
#include <stdlib.h>

#include "box_html.h"
#include "../utils/box_regex.h"


typedef box_document *document;

typedef box_element    *element;
typedef box_el_tags    *element_tags;
typedef box_el_content *element_content;

extern document box_read_document(char *filename, int *login);

#endif
