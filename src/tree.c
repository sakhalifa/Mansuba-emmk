#include "tree.h"

void vs_node_free(void *vn){
    node_free((node_t*)vn);
}

node_t *tree_create(void *val, void (*free_func)(void*)){
    node_t *n = malloc(sizeof(node_t));
    n->children = array_list_init(0, vs_node_free);
    n->parent = NULL;
    n->value = val;
    n->free_func = free_func;

    return n;
}

void node_add_child(node_t* node, void *val){
    node_t *n = tree_create(val, node->free_func);
    n->parent = node;
    array_list_push(node->children, n);
}

void node_remove_child(node_t *node, void* val, int (*cmp_func)(void*, void*)){
    int idx = array_list_get_index(node->children, val, cmp_func);
    if(idx != -1){
        node_free(array_list_remove(node->children, idx));
    }
}

node_t *tree_get_node(node_t *root, void* val, int (*cmp_func)(void*, void*)){
    if(root == NULL){
        return NULL;
    }
    for(int i = 0; i<root->children->len; i++){
        node_t* n = tree_get_node(array_list_get(root->children, i), val, cmp_func);
        if(n != NULL){
            return n;
        }
    }
    return NULL;
}

bool node_has_parent(node_t *node, void* val, int (*cmp_func)(void*, void*)){
    if(node == NULL){
        return false;
    }
    if(!cmp_func(val, node)){
        return true;
    }
    return node_has_parent(node->parent, val, cmp_func);
}

void node_free(node_t* root){
    if(root == NULL){
        return;
    }
    array_list_free(root->children);
    root->free_func(root->value);
    free(root);
}