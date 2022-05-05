#include "box_ntree.h"

struct box_ntree_node {
    
    struct box_ntree_node *parent;
    unsigned int child_count;

    void *value;

    box_array *array;

};

struct box_ntree {

    box_ntree_node *root;
    box_ntree_node *worker;

    /* Dynamic array data */
    size_t length;
    size_t size;

};


static void box_destroy_nodes(box_ntree_node *node, destroy_value destroy);

extern box_ntree *box_new_ntree(size_t length) {
    
    box_ntree *ntree = (box_ntree*)malloc(sizeof(box_ntree));

    ntree->root = NULL;
    ntree->worker = NULL;

    ntree->size = sizeof(box_ntree_node*);
    ntree->length = length;

    return ntree;
}

extern box_ntree *box_add_ntree_node(box_ntree *ntree) {

    box_ntree_node *node = (box_ntree_node*)malloc(sizeof(box_ntree_node));

    node->parent = ntree->worker;
    node->child_count = 0;

    node->value = NULL;
    node->array = box_new_array(ntree->length, ntree->size);

    if (ntree->root == NULL) {
        ntree->root = node;
    }
    else {
        box_ntree_node *parent = ntree->worker;

        box_put_array(parent->array, parent->child_count++, (void*)&node);
    }

    ntree->worker = node;

    return ntree;
}

extern void box_worker_up(box_ntree *ntree) {
    
    if (ntree->worker != NULL && ntree->worker->parent != NULL) {

       ntree->worker = ntree->worker->parent; 
    }
}

extern void box_traverse_ntree(box_ntree *ntree, pre_traverse pre, post_traverse post, void *data) {

    if (ntree->root != NULL) {
        box_traverse_nodes(ntree->root, pre, post, data);
    }
}

extern void box_traverse_nodes(box_ntree_node *node, pre_traverse pre, post_traverse post, void *data) {

    if (pre != NULL && pre(node, data) == 0) {

        for (unsigned int i = 0; i < node->child_count; ++i) {
            box_traverse_nodes(*(box_ntree_node**)box_get_array(node->array, i), pre, post, data);
        }

        if (post != NULL) {
            post(node, data);
        }
    }
}

extern void box_destroy_ntree(box_ntree *ntree, destroy_value destroy) {
    
    if (ntree->root != NULL) {
        box_destroy_nodes(ntree->root, destroy);
    }

    free(ntree);
}

static void box_destroy_nodes(box_ntree_node *node, destroy_value destroy) {

    for (unsigned int i = 0; i < node->child_count; ++i) {
        box_destroy_nodes(*(box_ntree_node**)box_get_array(node->array, i), destroy);
    }

    box_destroy_array(node->array);

    destroy(node->value);
 
    free(node);
}

extern void *box_ntree_node_get_value(box_ntree_node *node) {

    void *value = NULL;

    if (node != NULL) {
        value = node->value;
    }

    return value;
}

/* node value */
extern void *box_worker_get_value(box_ntree *ntree) {

    void *value = NULL;

    if (ntree->worker != NULL) {
        value = ntree->worker->value; 
    }

    return value;
}

extern void box_worker_set_value(box_ntree *ntree, void *value) {
    
    if (ntree->worker != NULL) {
        ntree->worker->value = value;
    }
}
