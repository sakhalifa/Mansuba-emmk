#ifndef __PLAYER_H__
#define __PLAYER_H__
#include "geometry.h" 

typedef struct player{
    color_t color;
} player_t;


player_t players[MAX_PLAYERS];


player get_random_player();



#endif // __PLAYER_H__
