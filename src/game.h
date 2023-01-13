#ifndef __GAME_H__
#define __GAME_H__

#include "util.h"
#include "moves.h"
#include "player.h"
#include "world.h"

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


/// @brief Allocates and initialize the game structure with the given parameters 
/// @param world the world 
/// @param max_turn the maximum number of turns
/// @param victory_type the type of victory used
/// @param player pointer on a player
/// @return a pointer of the game structure
game_t *game_init(struct world_t *world, uint max_turn, enum victory_type victory_type, player_t *player);



/// @brief Changes the game \p current_player field to the given player
/// @param game the game structure
/// @param player the player to put
void change_player(game_t *game, player_t *player);


/// @brief Returns the index of a random piece in the world for the given player  
/// @param game the game structure
/// @param player the player
/// @return the piece index in the world 
uint choose_random_piece_for_player(const game_t *game, const player_t *player);

/// @brief Returns a random game piece from the player captured pieces 
/// @param game the game structure 
/// @param player the player 
/// @return a copy of a captured game piece 
game_piece_t choose_random_captured_piece_for_player(const game_t* game, const player_t *player);

/// @brief Returns a random node inside the tree of the possible moves for the given piece index 
/// @param game the game structure
/// @param piece the index of a piece
/// @return a random node inside the move tree for the piece
node_t *choose_random_move_for_piece(const game_t* game, uint piece);


/// @brief Returns a node inside the tree of the possible moves for the given piece index that represents the best move. 
/// @param game the game structure
/// @param piece the index of a piece
/// @return a node inside the move tree for the piece
node_t *choose_best_move_for_piece(const game_t *game, uint piece);

/// @brief Plays the move given
/// @param game the game structure
/// @param move a node representing the move to make
void current_player_move_piece(game_t *game, const node_t *move);



/// @brief Tries to escape the given piece, if successful places it back in the world
/// @param game the game structure
/// @param piece the game piece
/// @return true if the escape was successful, false otherwise
bool current_player_try_escape(game_t *game, game_piece_t piece);


/// @brief Checks if the current game is in a win  
/// @param game the game structure
/// @return true if the game is won, false otherwise
bool check_win(const game_t *game);


/// @brief Displays the game board on the standard output.
/// @param game pointer on the game stucture
void display_game(const game_t *game);

/// @brief Displays the game grid on the standard output. To display available moves on top you need to pass a pointer to the move tree, otherwise pass NULL to ignore it.
/// @param game the game structure
/// @param moves the moves tree. Optionnal, can be NULL.
void display_grid(const game_t *game, const node_t *moves);


/// @brief Frees the game structure and all its fields
/// @param game the game structure
void game_free(game_t *game);


/// @brief Captures the piece at the index piece and pushes it inside the captured_pieces array_list
/// @param game the game structure 
/// @param index the piece index
void capture_piece_at(game_t *game, uint index);

/// @brief Places all the pieces stored in the starting_pos list into the world
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
