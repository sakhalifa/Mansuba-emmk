#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "../src/linked_list.h"
void free_nothing(void *_){
    _ = _;
}

void test_stack(){
    linked_list_t *l = linked_list_create(free_nothing);
    assert(linked_list_get_length(l) == 0);
    assert(linked_list_get_first(l) == NULL);
    assert(linked_list_get_last(l) == NULL);

    int a = 0;
    linked_list_push(l, &a);
    assert(linked_list_get_length(l) == 1);
    assert(linked_list_get_first(l) == &a);
    assert(linked_list_get_last(l) == &a);

    int b = 1;
    linked_list_push(l, &b);
    assert(linked_list_get_length(l) == 2);
    assert(linked_list_get_first(l) == &a);
    assert(linked_list_get_last(l) == &b);

    int c = 2;
    linked_list_queue(l, &c);
    assert(linked_list_get_length(l) == 3);
    assert(linked_list_get_first(l) == &c);
    assert(linked_list_get_last(l) == &b);

    linked_list_remove_first(l);
    assert(linked_list_get_length(l) == 2);
    assert(linked_list_get_first(l) == &a);
    assert(linked_list_get_last(l) == &b);

    linked_list_remove_last(l);
    assert(linked_list_get_length(l) == 1);
    assert(linked_list_get_first(l) == &a);
    assert(linked_list_get_last(l) == &a);
    linked_list_free(l);
}

void test_malloc(){
    linked_list_t *l = linked_list_create(free);
    assert(linked_list_get_length(l) == 0);
    assert(linked_list_get_first(l) == NULL);
    assert(linked_list_get_last(l) == NULL);

    int *a = malloc(sizeof(int));
    *a = 0;
    linked_list_push(l, a);
    assert(linked_list_get_length(l) == 1);
    assert(linked_list_get_first(l) == a);
    assert(linked_list_get_last(l) == a);

    int *b = malloc(sizeof(int));
    *b = 1;
    linked_list_push(l, b);
    assert(linked_list_get_length(l) == 2);
    assert(linked_list_get_first(l) == a);
    assert(linked_list_get_last(l) == b);

    int *c = malloc(sizeof(int));
    *c = 2;
    linked_list_queue(l, c);
    assert(linked_list_get_length(l) == 3);
    assert(linked_list_get_first(l) == c);
    assert(linked_list_get_last(l) == b);

    linked_list_remove_first(l);
    assert(linked_list_get_length(l) == 2);
    assert(linked_list_get_first(l) == a);
    assert(linked_list_get_last(l) == b);
    linked_list_remove_last(l);
    assert(linked_list_get_length(l) == 1);
    assert(linked_list_get_first(l) == a);
    assert(linked_list_get_last(l) == a);
    linked_list_free(l);
}

bool test_linked(){
    test_stack();
    test_malloc();
    return 1;
}