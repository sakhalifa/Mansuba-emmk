#ifndef __PROJECT_H__
#define __PROJECT_H__

#include "util.h"
#include "world.h"
#include "player.h"
#include "moves.h"
#include "geometry.h"
#include "neighbors.h"
#include <time.h>

enum victory_type{
    SIMPLE=0,
    COMPLEX=1
};

uint choose_random_piece_belonging_to(struct world_t *world, player_t *player);
node_t *choose_random_move_for_piece(struct world_t *world, uint piece);
void move_piece(struct world_t *world, node_t *move, player_t *player);

//populates the world as : first row full of black pawn, last row full of white pawn
void world_populate(struct world_t * world);


#endif // __PROJECT_H__
