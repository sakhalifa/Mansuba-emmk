#include <stdio.h>
#include <assert.h>
#include "array_list.h"

/**
 * Inits an array_list with an initial length and a function to free elements.
 */
struct array_list *array_list_init(size_t len, void (*free_func)(void *))
{
    size_t i;
    for (i = 1; i < len; i *= 2)
        ;
    array_list_t *ret = malloc(sizeof(array_list_t));
    assert(ret);
    ret->list = malloc(i * sizeof(void *));
    assert(ret->list);
    ret->len = 0;
    ret->allocated_len = i;
    ret->free_func = free_func;
    return ret;
}

void realloc_list(array_list_t *list)
{

    list->allocated_len *= 2;
    list->list = realloc(list->list, list->allocated_len * sizeof(void *));
    assert(list->list);
}

/**
 * Push an element onto the array_list at list->len
 */
void array_list_push(array_list_t *list, void *x)
{
    if (list->len + 1 > list->allocated_len)
    {
        realloc_list(list);
    }
    list->list[list->len] = x;
    list->len += 1;
}

/**
 * Gets an element from the array_list
 */
void *array_list_get(array_list_t *list, unsigned int idx)
{
    if (idx >= list->len)
    {
        return NULL;
    }
    return list->list[idx];
}

/**
 * Sets the element to index idx in array_list to val
 */
void array_list_set(array_list_t *list, void *val, unsigned int idx)
{
    if (idx < list->len)
    {
        list->list[idx] = val;
    }
}

/**
 * Removes the element at idx from array_list and returns it
 */
void *array_list_remove(array_list_t *list, int idx)
{
    void *element = list->list[idx];
    for (size_t i = idx + 1; i < list->len; i++)
    {
        list->list[i - 1] = list->list[i];
    }
    list->len -= 1;
    return element;
}

int array_list_get_index(array_list_t *l, void *val, int (*cmp_func)(void *, void *))
{
    for (int i = 0; i < (int)l->len; i++)
    {
        if (!cmp_func(val, array_list_get(l, i)))
        {
            return i;
        }
    }
    return -1;
}

bool array_list_contains(array_list_t *l, void *val, int (*cmp_func)(void *, void *))
{
    return array_list_get_index(l, val, cmp_func) != -1;
}

/**
 * Frees the array_list. This WILL free all the elements inside of it
 */
void array_list_free(array_list_t *array_list)
{
    for (size_t i = 0; i < array_list->len; i++)
    {
        array_list->free_func(array_list_get(array_list, i));
    }
    free(array_list->list);
    free(array_list);
}