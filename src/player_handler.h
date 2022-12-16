#ifndef __PLAYER_HANDLER_H__
#define __PLAYER_HANDLER_H__
#include "game.h"
#include "input.h"

uint read_player_piece(game_t *game);
node_t * get_player_move(game_t *game, uint piece_index);
void display_game_with_moves(game_t *game, node_t *moves);
enum actions get_player_action(game_t * game);

#endif // __PLAYER_HANDLER_H__
