#ifndef BOX_MAP_H
#define BOX_MAP_H

#include "box_array.h"

#include <string.h>
#include <stdlib.h>

typedef struct box_map_array box_map_array;

typedef struct box_map_node box_map_node;

extern box_map_array *box_new_map_array();

extern void box_destroy_map_array(box_map_array *array);

extern size_t box_get_map_array_length(box_map_array *array);

/* Two behaviors */
/* If value not null: Add value to values array and return updated values */
/* If value     null: Don't add value and return array of values if key exists */
extern box_array *box_map(box_map_array *array, char *key, void *value);

#endif
