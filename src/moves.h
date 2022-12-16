#ifndef __MOVES_H__
#define __MOVES_H__
#include "tree.h"
#include "world.h"
#include "position.h"

node_t *get_moves(struct world_t* world, position_t* pos, array_list_t *starting_pos);

void init_moves();

#endif