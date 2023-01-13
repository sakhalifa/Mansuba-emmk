#include "array_list.h"
#include "util.h"
//TODO Refactor

void test_stack(void){
    array_list_t *l;
    l = array_list_init(20, free_nothing);
    assert(array_list_length(l) == 0);
    int tab[1][20];
    // Add 20 elements to array_list
    for (int i = 0; i < 20; i++)
    {
        *tab[i] = 1;
        array_list_push(l, tab[i]);
    }

    // Sets the value of those 20 elements
    for(int i = 0; i<20; i++){
        *tab[i] = i;
        array_list_set(l, tab[i], i);
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

    // Push 1 element to reallocate again
    array_list_push(l, &a);

    // Check if elements were copied successfully
    for (int i = 0; i < 20; i++)
    {
        assert((*(int *)array_list_get(l, i)) == i);
    }
    for (int i = 20; i < (int)array_list_length(l); i++)
    {
        assert((*(int *)array_list_get(l, i)) == 20);
    }

    // Remove the last element before the 20 spam.
    array_list_remove(l, 19);
    assert(array_list_length(l) == 32);
    for (int i = 0; i < 19; i++)
    {
        assert((*(int *)array_list_get(l, i)) == i);
    }
    for (int i = 19; i < (int)array_list_length(l); i++)
    {
        assert((*(int *)array_list_get(l, i)) == 20);
    }

    // Create a 0-length array_list (will allocate for 1 element)
    array_list_t *zero_array = array_list_init(0, free_nothing);
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

void test_no_memory_leak(void){
    array_list_t *zero_array = array_list_init(0, free);
    for (int i = 0; i < 20; i++)
    {
        int *number = malloc(sizeof(int));
        array_list_push(zero_array, number);
    }

    array_list_free(zero_array);
}

bool test_array(void)
{
    test_stack();
    test_no_memory_leak();
    

    return true;
}
