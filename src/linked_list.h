#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__
#include <stdbool.h>
typedef struct cell cell_t;
struct linked_list;
typedef struct linked_list linked_list_t;

cell_t* cell_next(cell_t *c);
cell_t* cell_prev(cell_t *c);
void* cell_get_value(cell_t *c);
/**
 * Allocates a new linked list on the heap
*/
linked_list_t *linked_list_create(void (*free_func)(void *));
/**
 * Frees the linked list and all of its members
*/
void linked_list_free(linked_list_t *l);

void *linked_list_get_first(linked_list_t *l);
void *linked_list_get_last(linked_list_t *l);
int linked_list_get_length(linked_list_t *l);

/**
 * Removes the last element and frees it
 * Returns true iif an element was removed
*/
bool linked_list_remove_last(linked_list_t *l);
/**
 * Removes the first element and frees it
 * Returns true iif an element was removed
*/
bool linked_list_remove_first(linked_list_t *l);
/**
 * Adds an element to the end of the linked list
 */
void linked_list_push(linked_list_t *l, void* val);
/**
 * Adds an element to the start of the linked list
 */
void linked_list_queue(linked_list_t *l, void* val);

#endif