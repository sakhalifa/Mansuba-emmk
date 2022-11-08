#ifndef __ARRAY_LIST_H__
#define __ARRAY_LIST_H__
#include <stdlib.h>

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
void *array_list_get(array_list_t *list, int idx);

/**
 * Sets the element to index idx in array_list to val
*/
void array_list_set(array_list_t *list, void *val, int idx);

/**
 * Frees the array_list. Does NOT free the elements inside it.
*/
void array_list_free(array_list_t *array_list);



#endif