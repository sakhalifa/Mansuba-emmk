#include "configuration.h"

typedef struct
{
    bool allowed_sorts[MAX_SORT - 1];
    array_list_t *moves_for_sort[MAX_SORT - 1];
    bool capture_allowed;
    relation_t relation;
    bool is_locked;
    bool initialized;
} config_t;

config_t GLOBAL_CONFIG;

void panic_if_locked()
{
    if (GLOBAL_CONFIG.is_locked)
    {
        fprintf(stderr, "Error! Cannot change configuration while it is locked!\n");
        exit(EXIT_FAILURE);
    }
}

void init_config()
{
    if (GLOBAL_CONFIG.initialized)
        return;
    for (int i = 0; i < MAX_SORT - 1; i++)
    {
        GLOBAL_CONFIG.allowed_sorts[i] = false;
        GLOBAL_CONFIG.moves_for_sort[i] = array_list_init(0, free_nothing);
    }
    GLOBAL_CONFIG.initialized = true;
}

void add_allowed_sort(enum sort_t sort)
{
    init_config();
    GLOBAL_CONFIG.allowed_sorts[sort-1] = true;
}

int cmp_move(move_t m1, move_t m2){
    return !(m1 == m2);
}

void add_allowed_move_for_sort(move_t move, enum sort_t sort)
{
    init_config();
    if(!array_list_contains(GLOBAL_CONFIG.moves_for_sort[sort-1], move, (void*)cmp_move)){
        array_list_push(GLOBAL_CONFIG.moves_for_sort[sort-1], move);
    }
}

void set_capture_allowed(bool yes_no)
{
    GLOBAL_CONFIG.capture_allowed = yes_no;
}

void set_relation(relation_t relation)
{
    GLOBAL_CONFIG.relation = relation;
}

void lock_config()
{
    GLOBAL_CONFIG.is_locked = true;
}

bool is_sort_allowed(enum sort_t sort)
{
    return sort == NO_SORT || GLOBAL_CONFIG.allowed_sorts[sort - 1];
}

array_list_t *get_allowed_moves_for_sort(enum sort_t sort)
{
    return GLOBAL_CONFIG.moves_for_sort[sort-1];
}

relation_t get_relation()
{
    return GLOBAL_CONFIG.relation;
}

bool is_capture_allowed()
{
    return GLOBAL_CONFIG.capture_allowed;
}