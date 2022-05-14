#ifndef BOX_READER_H
#define BOX_READER_H

#include <stdio.h>
#include <stdlib.h>

#include "box_html.h"
#include "box_tags.h"
#include "../utils/box_regex.h"


typedef box_html_tree *box_file;

typedef box_html_element *element;

extern box_file box_read_file(char *filename);

extern void box_destroy_file(box_file file);

#endif
