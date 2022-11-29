#include <sys/time.h>
#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>
#include "game.h"
#include "neighbors.h"

void world_populate(struct world_t *world)
{
    for (int i = 0; i < HEIGHT; i++)
    {
        enum sort_t cur_sort = (i % (MAX_SORT - 1)) + 1;
        world_set(world, (i * WIDTH), BLACK);
        world_set_sort(world, (i * WIDTH), cur_sort);

        world_set(world, ((i + 1) * WIDTH) - 1, WHITE);
        world_set_sort(world, ((i + 1) * WIDTH) - 1, cur_sort);
    }
}

game_t *game_init(struct world_t *world, uint max_turn, enum victory_type victory_type, player_t *player)
{
    game_t *game = malloc(sizeof(game_t));
    game->world = world;
    game->current_player = player;
    game->max_turns = max_turn;
    game->turn = 0;
    game->victory_type = victory_type;
    game->captured_pieces_list = array_list_init(0, free);
    world_populate(game->world);
    return game;
}

uint choose_random_piece_belonging_to_current(game_t *game)
{
    uint positions[WORLD_SIZE];
    uint index = 0;
    for (uint i = 0; i < WORLD_SIZE; i++)
    {
        if (world_get(game->world, i) == game->current_player->color)
        {
            positions[index] = i;
            index++;
        }
    }

    assert(index != 0);
    return positions[rand() % index];
}

captured_piece_t choose_random_captured_piece_belonging_to_current(game_t *game){
    uint lgt = 0;
    captured_piece_t *tab = malloc(sizeof(uint)*game->captured_pieces_list->len);
    for(uint i = 0; i<game->captured_pieces_list->len; i++){
        captured_piece_t *piece = array_list_get(game->captured_pieces_list, i);
        if(piece->piece.color == game->current_player->color){
            tab[lgt++] = *piece;
        }
    }

    if(lgt == 0){
        captured_piece_t res = {.index=UINT_MAX};
        return res;
    }
    uint rand_int = rand() % lgt;
    captured_piece_t res = tab[rand_int];

    free(tab);
    return res;
}

void current_player_try_escape(game_t *game, captured_piece_t piece){
    if(world_get_sort(game->world, piece.index) == NO_SORT){
        int choice = rand() % 2;
        if(choice == 0){
            world_set_sort(game->world, piece.index, piece.piece.sort);
            world_set(game->world, piece.index, piece.piece.color);
        }
    }
}

node_t *choose_random_move_for_piece(game_t *game, uint piece)
{
    position_t position;
    position_from_idx(&position, piece);
    node_t *moves = get_moves(game->world, &position);

    uint len_children = moves->children->len;

    if (len_children == 0)
    {
        node_free(moves);
        return NULL;
    }

    uint selected_child = rand() % (len_children);
    node_t *move_ending = array_list_get(moves->children, selected_child);
    len_children = move_ending->children->len;
    selected_child = rand() % (len_children + 1);

    while (selected_child != len_children)
    {
        move_ending = array_list_get(move_ending->children, selected_child);
        len_children = move_ending->children->len;
        if (len_children == 0)
            break;
        selected_child = rand() % (len_children + 1);
    }

    return move_ending;
}

void current_player_move_piece(game_t *game, node_t *move)
{
    node_t *move_tree_root = node_get_root(move);
    uint destination_idx = position_to_idx((position_t *)move->value);
    uint source_idx = position_to_idx((position_t *)move_tree_root->value);
    enum sort_t source_sort = world_get_sort(game->world, source_idx);
    world_set(game->world, destination_idx, game->current_player->color);
    world_set_sort(game->world, destination_idx, source_sort);

    world_set_sort(game->world, source_idx, NO_SORT);
    world_set(game->world, source_idx, NO_COLOR);

    node_free(move_tree_root);

    return;
}

bool check_win(game_t *game)
{
    bool victoryB = true;
    bool victoryW = true;
    switch (game->victory_type)
    {
    case SIMPLE:
        for (int i = 0; i < HEIGHT; i++)
        {
            if (world_get(game->world, (i * WIDTH)) == WHITE)
            {
                return true;
            }
            if (world_get(game->world, ((i + 1) * WIDTH) - 1) == BLACK)
            {
                return true;
            }
        }
        return false;
    case COMPLEX:
        for (int i = 0; i < HEIGHT; i++)
        {
            if (world_get(game->world, (i * WIDTH)) != WHITE)
                victoryW = false;
            if (world_get(game->world, ((i + 1) * WIDTH) - 1) != BLACK)
                victoryB = false;
        }
        return victoryB || victoryW;

    default:
        return false;
    }
}

void display_game(game_t *game)
{
    for (int j = -2; j < WIDTH * 3; j++)
        printf("-");
    printf("\n");
    printf("|turn:%-5d", game->turn);
    for (int j = -2; j < (WIDTH * 3) - 13; j++)
        printf(" ");
    switch (get_neighbors_seed())
    {
    case SQUARE:
        printf("▢");
        break;
    case TRIANGULAR:
        printf("△");
        break;
    case HEXAGONAL:
        printf("⬡");
        break;
    default:
        printf("?");
        break;
    }

    printf("|\n");

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
            printf(" %s", place_to_string(world_get(game->world, i * WIDTH + j), world_get_sort(game->world, i * WIDTH + j)));
        }
        printf("|\n");
    }

    for (int j = -2; j < WIDTH * 3; j++)
    {
        printf("-");
    }
    printf("\n");
}
void change_player(game_t *game, player_t *player)
{
    game->current_player = player;
}