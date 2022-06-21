#include "box_map.h"

#define BOX_DYN_ARRAY_LENGTH 10

static box_map_node *box_map_new_node(box_map_array *array, char *key);

static box_map_node *box_map_get_by_key(box_map_array *array, char *key);

static void box_destroy_map_node(box_map_node *node);
typedef struct box_map_array {
   
    box_array *maps;
    size_t length;

} box_map_array;

typedef struct box_map_node {

    char      *key;
    box_array *values; // dynamic array of void pointers

    size_t length;

} box_map_node;

/* 
int main(void) {

    char *key1 = "ST 1";
    char *key2 = "ST 2";
    char *key3 = "ST 3";

    char *value1 = "VAL 1";
    char *value2 = "VAL 2";
    char *value3 = "VAL 3";
    char *value4 = "VAL 4";

    box_map_array *array = box_new_map_array();

    box_map(array, key1, (void *)value1);
    box_map(array, key2, (void *)value2);
    box_map(array, key3, (void *)value3);
    box_map(array, key3, (void *)value4);


    box_array *values = box_map(array, key3, NULL);

    for (int i = 0 ; ; ++i) {

        void *value = *(void**)box_get_array(values, i);
        
        if(value == NULL) break;

        printf("VALUE: %s\n", (char*)value);
    }

    box_destroy_map_array(array);

    return 0;
}
*/

extern box_map_array *box_new_map_array() {

    box_map_array *array = (box_map_array *)malloc(sizeof(box_map_array));

    *array = (box_map_array) {
        .maps = box_new_array(BOX_DYN_ARRAY_LENGTH, sizeof(box_map_node*)),
        .length = 0
    };

    return array;
}

extern void box_destroy_map_array(box_map_array *array) {

    if ( array != NULL ) {

        for (int i = 0; i < array->length; ++i) {
            box_destroy_map_node(*(box_map_node **)box_get_array(array->maps, i));
        }

        box_destroy_array(array->maps);

        free(array);
    }
}

static void box_destroy_map_node(box_map_node *node) {

    if (node != NULL) {

        box_destroy_array(node->values);
        free(node->key);

        free(node);
    }
}

extern size_t box_get_map_array_length(box_map_array *array) {

    if (array != NULL) return array->length;

    return 0;
}

/* Two behaviors */
/* If value not null: Add value to values array and return updated values */
/* If value     null: Don't add value and return array of values if key exists */
extern box_array *box_map(box_map_array *array, char *key, void *value) {

    if (key == NULL) return NULL;

    box_map_node *node = NULL;

    if (array != NULL) {

        node = box_map_get_by_key(array, key); 

        if (value == NULL) {

            if ( node == NULL ) return NULL;

            return node->values;

        }

        if (node != NULL) {

            for (int i = 0; i < node->length; ++i) {

                if (*(void **)box_get_array(node->values, i) == value) return node->values;
            }
        }
        else node = box_map_new_node(array, key);

        box_put_array(node->values, node->length++, &value);
        return node->values;
    }
}

static box_map_node *box_map_new_node(box_map_array *array, char *key) {

    box_map_node *node = NULL;

    if (array != NULL ) {
        node = (box_map_node *)malloc(sizeof(box_map_node)); 

        *node = (box_map_node) {
            .length = 0,
            .key = (char *) calloc(strlen(key)+1, sizeof(char)),
            .values = box_new_array(BOX_DYN_ARRAY_LENGTH, sizeof(void *))
        };

        strncpy(node->key, key, strlen(key));

        box_put_array(array->maps, array->length++, &node);
    }

    return node;
}


static box_map_node *box_map_get_by_key(box_map_array *array, char *key) {

    box_map_node *tmp = NULL;

    for (int i = 0; i < array->length; ++i) {

        tmp = *(box_map_node **)box_get_array(array->maps, i); 

        if (strcmp(key, tmp->key) == 0) return tmp;
    }

    return NULL;
}
