#include "moves.h"
#include "neighbors.h"
#include "util.h"


node_t *get_moves(struct world_t* world, position_t* pos){
    position_t *malloc_pos = malloc(sizeof(position_t));
    malloc_pos->col = pos->col;
    malloc_pos->row = pos->row;
    return tree_create(pos, free);
}