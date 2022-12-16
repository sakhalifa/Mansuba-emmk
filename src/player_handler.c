#include "player_handler.h"

uint read_player_piece(game_t *game){
    printf("Choose your piece\n");

    uint index = read_user_position();
    if (index == UINT_MAX) return read_player_piece(game);
    
    position_t position;
    position_from_idx(&position, index);

    if(world_get_sort(game->world, index) == NO_SORT){
        printf("There is no piece at the position %u,%u !\n", position.row, position.col);
        return read_player_piece(game);
    }

    if(world_get(game->world, index) != game->current_player->color){
        printf("The piece at %u,%u isn't yours !\n", position.row, position.col);
        return read_player_piece(game);
    }

    return index;
}

void display_game_with_moves(game_t *game, node_t *moves){

    for (int j = -2; j < WIDTH * 3; j++)
    {
        printf("-");
    }
    printf("\n");

    for (int i = 0; i < HEIGHT; i++)
    {
        printf("|");
        for (int j = 0; j < WIDTH; j++)
        {
            position_t position;
            position_from_idx(&position, i*WIDTH+j);
            if(tree_get_node(moves, (void*) &position, (void*) cmp_positions) != NULL){
                printf("\x1B[31m");
            }
            printf(" %s", place_to_string(world_get(game->world, i * WIDTH + j), world_get_sort(game->world, i * WIDTH + j)));
            printf("\x1B[0m");
        }
        printf("|\n");
    }

    for (int j = -2; j < WIDTH * 3; j++)
    {
        printf("-");
    }
    printf("\n");
}

node_t * get_player_move(game_t *game, uint piece_index){
    position_t position;
    position_from_idx(&position, piece_index);
    node_t *moves = get_moves(game->world, &position, game->starting_position);
    
    display_game_with_moves(game, moves);
    printf("Chose your move : \n");

    uint index = read_user_position();
    if (index == UINT_MAX) return get_player_move(game, piece_index);
    position_t chosen_position;
    position_from_idx(&chosen_position, index);

    //TODO switch tree print to display row col instead of col row 
    node_t *player_move = tree_get_node(moves, &chosen_position, (void*)cmp_positions);
    if (player_move == NULL) return get_player_move(game, piece_index);

    return player_move;
}

void display_available_action(game_t *game){
    printf(":w\tWAIT\n");
    printf(":m\tMOVE\n");
    if (has_piece_captured(game, game->current_player)) printf(":e\tESCAPE\n");
    
}

enum actions get_player_action(game_t * game){
    display_available_action(game);
    uint action = read_user_action();
    if (action == MAX_ACTION) return get_player_action(game);

    if(!has_piece_captured(game, game->current_player) && action == ESCAPE) return get_player_action(game);
    return action;
}
