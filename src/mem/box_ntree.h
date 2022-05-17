#ifndef BOX_NTREE_H
#define BOX_NTREE_H

#include <stdlib.h>
#include <string.h>

#include "box_array.h"

typedef struct box_ntree_node box_ntree_node;

typedef struct box_ntree box_ntree;

typedef void (*destroy_value)(void *);
typedef  int ( *pre_traverse)(box_ntree_node *, void *data);
typedef void (*post_traverse)(box_ntree_node *, void *data);

typedef void* (*copy_value)(void *);

extern box_ntree *box_new_ntree(size_t length);

extern box_ntree *box_add_ntree_node(box_ntree *ntree);

extern box_ntree_node *box_ntree_ploriferate(box_ntree *ntree, box_ntree_node *node, int size, copy_value copy, destroy_value destroy);

extern box_ntree_node *box_ntree_node_clone(box_ntree *ntree, box_ntree_node *node, copy_value copy);

extern void box_traverse_ntree(box_ntree *ntree, pre_traverse pre, post_traverse post, void *data);

extern void box_traverse_nodes(box_ntree_node *node, pre_traverse pre, post_traverse post, void *data);

extern void box_destroy_ntree(box_ntree *ntree, destroy_value destroy);

extern void box_worker_up(box_ntree *ntree);

extern void *box_ntree_node_get_value(box_ntree_node *node);

extern box_ntree_node *box_ntree_get_worker(box_ntree *ntree);

/* node value */
extern void *box_worker_get_value(box_ntree *ntree);
extern void  box_worker_set_value(box_ntree *ntree, void *value);

extern void *box_ntree_get_value(box_ntree_node *node);
extern void box_ntree_set_value(box_ntree_node *node, void *value);

extern int  box_ntree_get_children_count(box_ntree_node *node);

extern box_ntree_node *box_ntree_get_node_child(box_ntree_node *node, int index);

#endif
