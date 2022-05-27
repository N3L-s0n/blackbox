#include "box_array.h"

extern box_array *box_new_array(size_t length, size_t size) {
    box_array *array = (box_array*)malloc(sizeof(box_array));

    array->length = length;
    array->size = size;

    array->array = (char*)calloc(size*length,sizeof(char));

    return array;
}

extern int box_check_value_in_array(box_array *array, void *value) {

    if (array == NULL || value == NULL) return 1;

    for (int i = 0; i < array->length; ++i) {

        void * tmp = *(void**)(array->array + i*array->size);
        if(tmp == NULL) break;

        if(memcmp(tmp, value, array->size) == 0) return 0;
    }

    return 1;
}

extern void *box_put_array(box_array *array, unsigned int index, void *value) {

    if (index >= array->length && index < array->length*2) {
        box_resize_array(array);
    }

    if (index < array->length) {
        memcpy(array->array + index*array->size, value, array->size);
    }

    return value;
}

extern void *box_get_array(box_array *array, unsigned int index) {

    void *value = NULL;

    if (index < array->length) {
        value = array->array + index*array->size; 
    }

    return value;
}

extern void box_resize_array(box_array *array) {
    
    array->length *= 2;

    array->array = (char*)realloc(array->array, sizeof(char)*array->size*array->length);
}

extern void box_destroy_array(box_array *array) {
    
    if (array != NULL) {

        if (array->array != NULL) {
            free(array->array);
        }

        free(array);
    }
}

extern size_t box_size_array(box_array *array) {
    size_t size = 0;

    if (array != NULL) {
        size = array->size; 
    }

    return size;
}

extern size_t box_length_array(box_array *array) {
    size_t length = 0;

    if (array != NULL) {
        length = array->length; 
    }

    return length;
}

