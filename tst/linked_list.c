#include "linked_list.h"
#include "util.h"

void test_linked_list_create(void)
{
    linked_list_t *l = linked_list_create(free_nothing);
    assert(linked_list_length(l) == 0);
    assert(linked_list_get_first(l) == NULL);
    assert(linked_list_get_last(l) == NULL);
    linked_list_free(l);
}

void test_linked_list_free_stack(void)
{
    linked_list_t *l = linked_list_create(free_nothing);
    int tab[1][20];
    for(int i = 0; i<20; i++){
        *tab[i] = i;
        linked_list_push(l, tab[i]);
    }
    linked_list_free(l);
}

void test_linked_list_free_malloc(void)
{
    linked_list_t *l = linked_list_create(free);
    for(int i = 0; i<20; i++){
        int *a = malloc(sizeof(int));
        *a = i;
        linked_list_push(l, a);
    }
    linked_list_free(l);
}

void test_linked_list_free(void)
{
    test_linked_list_free_stack();
    test_linked_list_free_malloc();
}

void test_linked_list_get_first(void)
{
    linked_list_t *l = linked_list_create(free_nothing);
    int a, b, c;
    assert(linked_list_get_first(l) == NULL);
    linked_list_push(l, &a);
    assert(linked_list_get_first(l) == &a);
    linked_list_push(l, &b);
    assert(linked_list_get_first(l) == &a);
    linked_list_queue(l, &c);
    assert(linked_list_get_first(l) == &c);
    linked_list_free(l);
}

void test_linked_list_get_last(void)
{
    linked_list_t *l = linked_list_create(free_nothing);
    int a, b, c;
    assert(linked_list_get_last(l) == NULL);
    linked_list_push(l, &a);
    assert(linked_list_get_last(l) == &a);
    linked_list_queue(l, &b);
    assert(linked_list_get_last(l) == &a);
    linked_list_push(l, &c);
    assert(linked_list_get_last(l) == &c);
    linked_list_free(l);
}

void test_linked_list_length(void)
{
    linked_list_t *l = linked_list_create(free_nothing);
    int a, b;
    assert(linked_list_length(l) == 0);
    for (int i = 0; i < 20; i++)
    {
        linked_list_push(l, &a);
    }
    assert(linked_list_length(l) == 20);
    for (int i = 0; i < 20; i++)
    {
        linked_list_queue(l, &b);
    }
    assert(linked_list_length(l) == 40);
    for (int i = 0; i < 20; i++)
    {
        linked_list_remove_first(l);
    }
    assert(linked_list_length(l) == 20);
    for (int i = 0; i < 20; i++)
    {
        linked_list_remove_last(l);
    }
    assert(linked_list_length(l) == 0);
    linked_list_free(l);
}

void test_linked_list_remove_last(void)
{
    linked_list_t *l = linked_list_create(free_nothing);
    assert(linked_list_remove_last(l) == false);
    int tab[1][20];
    for (int i = 0; i < 20; i++)
    {
        *tab[i] = i;
        linked_list_push(l, tab[i]);
    }
    assert(linked_list_get_last(l) == tab[19]);
    assert(linked_list_remove_last(l));
    assert(linked_list_get_last(l) == tab[18]);
    assert(linked_list_length(l) == 19);
    linked_list_free(l);
}

void test_linked_list_remove_first(void)
{
    linked_list_t *l = linked_list_create(free_nothing);
    assert(linked_list_remove_first(l) == false);
    int tab[1][20];
    for (int i = 0; i < 20; i++)
    {
        *tab[i] = i;
        linked_list_queue(l, tab[i]);
    }
    assert(linked_list_get_first(l) == tab[19]);
    assert(linked_list_remove_first(l));
    assert(linked_list_get_first(l) == tab[18]);
    assert(linked_list_length(l) == 19);
    linked_list_free(l);
}

void test_linked_list_push(void)
{
    linked_list_t *l = linked_list_create(free_nothing);
    int a, b;
    assert(linked_list_get_first(l) == NULL);
    assert(linked_list_get_last(l) == NULL);
    linked_list_push(l, &a);
    assert(linked_list_get_first(l) == &a);
    assert(linked_list_get_last(l) == &a);
    linked_list_push(l, &b);
    assert(linked_list_get_first(l) == &a);
    assert(linked_list_get_last(l) == &b);
    linked_list_free(l);
}

void test_linked_list_queue(void)
{
    linked_list_t *l = linked_list_create(free_nothing);
    int a, b;
    assert(linked_list_get_first(l) == NULL);
    assert(linked_list_get_last(l) == NULL);
    linked_list_queue(l, &a);
    assert(linked_list_get_first(l) == &a);
    assert(linked_list_get_last(l) == &a);
    linked_list_queue(l, &b);
    assert(linked_list_get_first(l) == &b);
    assert(linked_list_get_last(l) == &a);
    linked_list_free(l);
}

bool test_linked_list(void)
{
    test_linked_list_create();
    test_linked_list_free();
    test_linked_list_get_first();
    test_linked_list_get_last();
    test_linked_list_length();
    test_linked_list_remove_last();
    test_linked_list_remove_first();
    test_linked_list_push();
    test_linked_list_queue();
    return true;
}