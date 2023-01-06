#ifndef __PLAYER_H__
#define __PLAYER_H__
#include <stdbool.h> 
#include "geometry.h" 
 
typedef struct player{
    enum color_t color;
    bool automated;     
} player_t;

/// @brief Gets a random player
/// @return a pointer on a random player
player_t *get_random_player(void);

/// @brief Inits the player array
/// @param real_players the number of human player 
void init_players(uint real_players);

/// @brief Returns a pointer on the next player from the current player
/// @param player a pointer on a player
/// @return a pointer on the next player  
player_t *next_player(player_t *player);

#endif // __PLAYER_H__
