#include "player_handler.h"

uint read_player_piece(const game_t *game){
    printf("Choose your piece (format is 'row col')\n");

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

void display_game_with_moves(const game_t *game, const node_t *moves){

    display_grid(game, moves);
}

node_t * get_player_move(const game_t *game, uint piece_index){
    position_t position;
    position_from_idx(&position, piece_index);
    node_t *moves = get_moves(game->world, &position, game->starting_position);
    
    display_game_with_moves(game, moves);
    printf("Chose your move : \n");

    uint index = read_user_position();
    if (index == UINT_MAX) return get_player_move(game, piece_index);
    position_t chosen_position;
    position_from_idx(&chosen_position, index);

    node_t *player_move = tree_get_node(moves, &chosen_position, (void*)cmp_positions);
    if (player_move == NULL) return get_player_move(game, piece_index);

    return player_move;
}

void display_available_action(const game_t *game){
    printf(":w\tWAIT\n");
    printf(":m\tMOVE\n");
    if (has_piece_captured(game, game->current_player)) printf(":e\tESCAPE\n");
    
}

enum actions get_player_action(const game_t * game){
    display_available_action(game);
    uint action = read_user_action();
    if (action == MAX_ACTION) return get_player_action(game);

    if(!has_piece_captured(game, game->current_player) && action == ESCAPE) return get_player_action(game);
    return action;
}


game_piece_t get_player_captured_piece(const game_t *game, const player_t * player){
    printf("Captured pieces :\n");
    uint player_piece_counter = 0;
    
    for (size_t i = 0; i < array_list_length(game->captured_pieces_list); i++)
    {
        game_piece_t *piece = array_list_get(game->captured_pieces_list, i);
        if(piece->piece.color == player->color){
            position_t piece_position;
            position_from_idx(&piece_position, piece->index);
            printf("%u : %s at %d,%d\n", player_piece_counter+1, place_to_string(piece->piece.color, piece->piece.sort), piece_position.row, piece_position.col);
            player_piece_counter++;
        }
    }
    
    uint choice = read_user_number() - 1;
    if (choice >= player_piece_counter) return get_player_captured_piece(game, player);
    game_piece_t final_piece;
    final_piece.index = UINT_MAX;

    for (size_t i = 0; i < array_list_length(game->captured_pieces_list); i++)
    {
        game_piece_t *piece = array_list_get(game->captured_pieces_list, i);
        if(piece->piece.color == player->color){
            player_piece_counter--;
            if (player_piece_counter == 0){
                final_piece.index = piece->index;
                final_piece.piece.color = piece->piece.color;
                final_piece.piece.sort = piece->piece.sort;
                return final_piece;
            }
        }
    }
    
    return final_piece;
}