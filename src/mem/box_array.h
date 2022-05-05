#ifndef BOX_ARRAY_H
#define BOX_ARRAY_H

#include <stdlib.h>
#include <string.h>

typedef struct box_array {
    
    size_t length;
    size_t size;

    char *array;

} box_array;

extern box_array *box_new_array(size_t length, size_t size);

extern void *box_put_array(box_array *array, unsigned int index, void *value);

extern void *box_get_array(box_array *array, unsigned int index);

extern void box_resize_array(box_array *array);

extern void box_destroy_array(box_array *array);

extern size_t box_size_array(box_array *array);

extern size_t box_length_array(box_array *array);

#endif
