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

extern box_ntree *box_new_ntree(size_t length);

extern box_ntree *box_add_ntree_node(box_ntree *ntree);

extern void box_traverse_ntree(box_ntree *ntree, pre_traverse pre, post_traverse post, void *data);

extern void box_traverse_nodes(box_ntree_node *node, pre_traverse pre, post_traverse post, void *data);

extern void box_destroy_ntree(box_ntree *ntree, destroy_value destroy);

extern void box_worker_up(box_ntree *ntree);

extern void *box_ntree_node_get_value(box_ntree_node *node);

/* node value */
extern void *box_worker_get_value(box_ntree *ntree);
extern void  box_worker_set_value(box_ntree *ntree, void *value);

#endif
