#ifndef __PLAYER_HANDLER_H__
#define __PLAYER_HANDLER_H__
#include "game.h"
#include "input.h"

/// @brief get the piece index from the standard input and makes sure it's allowed for the player
/// @param game the game structure 
/// @return the index of the chosen piece 
uint read_player_piece(const game_t *game);

/// @brief gets the move chosen by the player inside all the possible moves for the given piece index
/// @param game the game structure
/// @param piece_index the index of the piece to get the moves 
/// @return the chosen node of the move tree 
node_t * get_player_move(const game_t *game, uint piece_index);

/// @brief displays the game world on the standard output with highlighted cells matching the cells inside the \p moves tree
/// @param game the game structure
/// @param moves the move tree
void display_game_with_moves(const game_t *game, const node_t *moves);

/// @brief displays the possible actions for the current player on the standard output and returns the action chosen by the player
/// @param game the game structure
/// @return the chosen action
enum actions get_player_action(const game_t * game);

/// @brief displays the current captured pieces for \p player on the standard output and returns the piece chosen by the player  
/// @param game the game structure
/// @param player the player for which we are getting the captured pieces
/// @return the game_piece chosen by the player 
game_piece_t get_player_captured_piece(game_t *game, player_t * player);

#endif // __PLAYER_HANDLER_H__
