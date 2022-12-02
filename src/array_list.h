#ifndef __ARRAY_LIST_H__
#define __ARRAY_LIST_H__
#include <stdlib.h>
#include <stdbool.h>

typedef struct array_list{
    void **list;
    size_t len;
    size_t allocated_len;
    void (*free_func)(void *);
} array_list_t;

/**
 * Inits an array_list with an initial length and a function to free elements.
 * It is allocated on the heap.
*/
struct array_list *array_list_init(size_t len, void (*free_func)(void *));

/**
 * Push an element onto the array_list at list->len
*/
void array_list_push(array_list_t *list, void *x);

/**
 * Removes the element at idx from array_list and returns it
*/
void *array_list_remove(array_list_t *list, int idx);

/**
 * Gets an element from the array_list
*/
void *array_list_get(array_list_t *list, unsigned int idx);

/**
 * Sets the element to index idx in array_list to val
*/
void array_list_set(array_list_t *list, void *val, unsigned int idx);

/**
 * Returns true iif the array_list contains the value within the interval [0,l->len[
 * Checks equality using cmp_func.
*/
bool array_list_contains(array_list_t *l, void *val, int (*cmp_func)(void*, void*));

/**
 * If val is in the array_list within [0, l->len[, returns its index.
 * Else, returns -1
*/
int array_list_get_index(array_list_t *l, void *val, int (*cmp_func)(void*, void*));
/**
 * Frees the array_list. This WILL free all the elements inside of it.
*/
void array_list_free(array_list_t *array_list);





#endif