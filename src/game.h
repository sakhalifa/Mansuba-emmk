#ifndef __GAME_H__
#define __GAME_H__

#include "util.h"
#include "moves.h"
#include "world.h"
#include "player.h"
#include "neighbors.h"

extern int verbose;

enum victory_type{
    SIMPLE=0,
    COMPLEX=1
};

typedef struct {
    uint turn;
    uint max_turns;
    player_t *current_player;
    enum victory_type victory_type;
    struct world_t *world;
    array_list_t *captured_pieces_list;
    array_list_t *starting_position;
} game_t;

struct game_result
{
    enum color_t winner;
    uint turns;
};

game_t *game_init(struct world_t *world, uint max_turn, enum victory_type victory_type, player_t *player);

void change_player(game_t *game, player_t *player);

uint choose_random_piece_for_player(const game_t *game, const player_t *player);
game_piece_t choose_random_captured_piece_for_player(const game_t* game, const player_t *player);

node_t *choose_random_move_for_piece(const game_t* game, uint piece);
node_t *choose_best_move_for_piece(const game_t *game, uint piece);

void current_player_move_piece(game_t *game, const node_t *move);

//return if the escape was successful or not
bool current_player_try_escape(game_t *game, game_piece_t piece);

/// @brief Checks if the current game is in a win  
/// @param game the game structure
/// @return true if the game is won, false otherwise
bool check_win(const game_t *game);


/// @brief displays the game board on the standard output
/// @param game pointer on the game stucture
void display_game(const game_t *game);

void display_grid(const game_t *game, const node_t *moves);


/// @brief Frees the game structure and all it's allocated memory
/// @param game the game structure
void game_free(game_t *game);

void capture_piece_at(game_t *game, uint index);

/// @brief places all the pieces stored in the starting_pos list into the world
/// @param game the game structure containing the world and the starting_pos
void world_populate(const game_t *game);

/// @brief initialize the starting_pos field with default placement
/// @details the default starting_pos are the first and last column of the game world, alternating between all the pieces sorts starting with a pawn.
/// @param game the game structure  
void load_starting_position(game_t *game);


/// @brief Checks if the given player has at least one piece captured 
/// @param game the game structure
/// @param player the player to check 
/// @return true if the player has a piece captured, false otherwise 
bool has_piece_captured(const game_t *game, const player_t *player);
#endif // __GAME_H__
