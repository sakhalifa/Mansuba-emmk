#ifndef __PLAYER_HANDLER_H__
#define __PLAYER_HANDLER_H__
#include "game.h"
#include "input.h"

uint read_player_piece(game_t *game);
void display_game_with_moves(game_t *game, node_t *moves);
node_t * read_player_move(game_t *game, uint piece_index);


#endif // __PLAYER_HANDLER_H__
