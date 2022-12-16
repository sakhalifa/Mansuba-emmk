#ifndef __PLAYER_H__
#define __PLAYER_H__
#include "geometry.h" 

typedef struct player{
    enum color_t color;
} player_t;

player_t *get_random_player();
void init_players();
player_t *next_player(player_t *);

#endif // __PLAYER_H__
