#ifndef __CONFIGURATION_H__
#define __CONFIGURATION_H__
#include "tree.h"
#include "util.h"
#include "array_list.h"
#include "world.h"

typedef void (*move_t)(struct world_t *world, node_t *root, uint source_index, array_list_t *starting_pos);

void add_allowed_sort(enum sort_t sort);

void add_allowed_move_for_sort(move_t move, enum sort_t sort);

void set_capture_allowed(bool yes_no);

void set_relation(relation_t relation);

void lock_config(void);

bool is_sort_allowed(enum sort_t sort);

array_list_t *get_allowed_moves_for_sort(enum sort_t sort);

relation_t get_relation(void);

bool is_capture_allowed(void);

void config_free(void);

#endif