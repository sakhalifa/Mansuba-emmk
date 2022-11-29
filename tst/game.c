#include "game.h"

void test_choose_random_captured_piece(){
    struct world_t *world = world_init();
    player_t player = {.color=WHITE};
    game_t *game = game_init(world, 1, SIMPLE, &player);

    position_t test_pos = {1, 1};
    captured_piece_t *p = malloc(sizeof(captured_piece_t));
    p->index = position_to_idx(&test_pos);
    p->piece.sort = PAWN;
    p->piece.color = WHITE;
    array_list_push(game->captured_pieces_list, p);

    captured_piece_t res = choose_random_captured_piece_belonging_to_current(game);
    assert(p->index == res.index);
    assert(p->piece.color == res.piece.color);
    assert(p->piece.sort == res.piece.sort);

    game_free(game);
    
}

void test_game(){
    test_choose_random_captured_piece();
}