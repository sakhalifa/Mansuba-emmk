#ifndef __MOVES_H__
#define __MOVES_H__
#include "array_list.h"
#include "world.h"
#include "position.h"

typedef struct move {
    position_t from;
    position_t to;
} move_t;

/**
 * Returns all the possibles moves for the piece at index idx in world world
*/
array_list_t *get_moves(struct world_t *world, int idx);

void init_move(move_t *ptr_m, int f_idx, int t_idx);

int cmp_moves(move_t *m1, move_t *m2);
#endif