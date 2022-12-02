#include "array_list.h"
#include "util.h"
//TODO Refactor

static void free_nothing(void *_)
{
    _ = _; // Remove warning lol
}

void test_stack(){
    array_list_t *l;
    l = array_list_init(20, free_nothing);
    assert(l->len == 0);
    assert(l->allocated_len == 32);
    int tab[1][20];
    l->len = 20;
    for (int i = 0; i < 20; i++)
    {
        *tab[i] = i;
        array_list_set(l, tab[i], (uint)i);
    }
    for (int i = 0; i < 20; i++)
    {
        assert((*(int *)array_list_get(l, i)) == i);
    }
    int a = 20;
    // Push elements just before needing to reallocate
    for (int i = 0; i < 32 - 20; i++)
    {
        array_list_push(l, &a);
    }
    assert(l->allocated_len == 32);

    // Push 1 element to reallocate again
    array_list_push(l, &a);
    assert(l->allocated_len == 64);

    // Check if elements were copied successfully
    for (int i = 0; i < 20; i++)
    {
        assert((*(int *)array_list_get(l, i)) == i);
    }
    for (int i = 20; i < (int)l->len; i++)
    {
        assert((*(int *)array_list_get(l, i)) == 20);
    }

    // Remove the last element before the 20 spam.
    array_list_remove(l, 19);
    assert(l->len == 32);
    for (int i = 0; i < 19; i++)
    {
        assert((*(int *)array_list_get(l, i)) == i);
    }
    for (int i = 19; i < (int)l->len; i++)
    {
        assert((*(int *)array_list_get(l, i)) == 20);
    }

    // Create a 0-length array_list (will allocate for 1 element)
    array_list_t *zero_array = array_list_init(0, free_nothing);
    assert(zero_array->allocated_len == 1);
    for (int i = 0; i < 20; i++)
    {
        *tab[i] = i;
        array_list_push(zero_array, tab[i]);
    }

    for (int i = 0; i < 20; i++)
    {
        assert((*(int *)array_list_get(zero_array, i)) == i);
    }

    array_list_free(l);
    array_list_free(zero_array);
}

void test_no_memory_leak(){
    array_list_t *zero_array = array_list_init(0, free);
    for (int i = 0; i < 20; i++)
    {
        int *number = malloc(sizeof(int));
        array_list_push(zero_array, number);
    }

    array_list_free(zero_array);
}

bool test_array()
{
    test_stack();
    test_no_memory_leak();
    

    return true;
}
