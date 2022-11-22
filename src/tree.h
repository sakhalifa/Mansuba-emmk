#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__
#include <stdbool.h>
#include "array_list.h"

/**
 * A node structure.
 * Every child of a node must have the same free_func as its parent.
*/
typedef struct node{
    void *value;
    void (*free_func)(void*);
    struct node* parent;
    array_list_t *children;
} node_t;

node_t *tree_create(void *val, void (*free_func)(void*));

node_t *node_add_child(node_t* node, void *val);

node_t *node_remove_child(node_t *node, void* val, int (*cmp_func)(void*, void*));

node_t *tree_get_node(node_t *root, void* val, int (*cmp_func)(void*, void*));

bool node_has_child(node_t *node, void* val, int (*cmp_func)(void*, void*));
bool node_has_parent(node_t *node, void* val, int (*cmp_func)(void*, void*));

void tree_print(node_t* root, void (*printValue)(void*));

void node_free(node_t* root);

#endif