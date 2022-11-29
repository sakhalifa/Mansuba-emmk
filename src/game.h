#ifndef __PROJECT_H__
#define __PROJECT_H__

#include "util.h"
#include "world.h"
#include "player.h"
#include "moves.h"
#include "neighbors.h"

enum victory_type{
    SIMPLE=0,
    COMPLEX=1
};

typedef struct {
    uint index;
    piece_t piece;
} captured_piece_t;

typedef struct {
    uint turn;
    uint max_turns;
    player_t *current_player;
    enum victory_type victory_type;
    struct world_t *world;
    array_list_t *captured_pieces_list;
} game_t;

struct game_result
{
    int winner;
    uint turns;
};

game_t *game_init(struct world_t *world, uint max_turn, enum victory_type victory_type, player_t *player);

void change_player(game_t *game, player_t *player);

uint choose_random_piece_belonging_to_current(game_t *game);    
node_t *choose_random_move_for_piece(game_t* game, uint piece);
void current_player_move_piece(game_t *game, node_t *move);
bool check_win(game_t *game);

void display_game(game_t *game);



#endif // __PROJECT_H__
