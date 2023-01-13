#ifndef __MOVES_H__
#define __MOVES_H__
#include "tree.h"
#include "util.h"
#include "position.h"
#include "world.h"

typedef enum {
    SIMPLE_MOVE = 0,
    SIMPLE_JUMP = 1,
    MULTIPLE_JUMP = 2,
    MAX_MOVES = 3
} move_type_t;

node_t *get_moves(struct world_t* world, position_t* pos, array_list_t *starting_pos);

void enable_move_type(move_type_t move_type);

#endif