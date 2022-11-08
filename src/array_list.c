#include "array_list.h"

/**
 * Inits an array_list with an initial length and a function to free elements.
*/
struct array_list *array_list_init(size_t len, void (*free_func)(void *)){
    int i;
    for(i = 1; i<len; i*=2);
    array_list_t *ret = malloc(sizeof(array_list_t));
    ret->list = malloc(len*sizeof(void*));
    ret->len = len;
    ret->allocated_len = i;
    ret->free_func = free_func;
    return ret;
}

void realloc_list(array_list_t *list){
    list->allocated_len *= 2;
    list->list = realloc(list->list, list->allocated_len);
}

/**
 * Push an element onto the array_list
*/
void array_list_push(array_list_t *list, void *x){
    if(list->len+1 > list->allocated_len){
        realloc_list(list);
    }
    list->list[list->len] = x;
    list->len += 1;
}

/**
 * Removes the element at idx from array_list and returns it
*/
void *array_list_remove(array_list_t *list, int idx){
    void *element = list->list[idx];
    for(int i = idx+1; i<list->len; i++){
        list->list[i-1] = list->list[i];
    }
    list->len -= 1;
    return element;
}

/**
 * Frees the array_list. Does NOT free the elements inside it.
*/
void array_list_free(array_list_t *array_list){
    free(array_list->list);
    free(array_list);
}