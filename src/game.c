#include <sys/time.h>
#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>
#include "game.h"
#include "neighbors.h"

void load_starting_position(game_t *game)
{
    for (int i = 0; i < HEIGHT; i++)
    {
        game_piece_t *game_piece = malloc(sizeof(game_piece_t));
        game_piece_t *game_piece_bis = malloc(sizeof(game_piece_t));
        enum sort_t current_sort = (i % (MAX_SORT - 1)) + 1;

        game_piece->index = (i * WIDTH);
        game_piece->piece.color = BLACK;
        game_piece->piece.sort = current_sort;

        game_piece_bis->index = ((i + 1) * WIDTH) - 1;
        game_piece_bis->piece.color = WHITE;
        game_piece_bis->piece.sort = current_sort;

        array_list_push(game->starting_position, game_piece);
        array_list_push(game->starting_position, game_piece_bis);
    }
}

void world_populate(game_t *game)
{
    for (size_t i = 0; i < game->starting_position->len; i++)
    {
        game_piece_t *game_piece = array_list_get(game->starting_position, i);
        world_set(game->world, game_piece->index, game_piece->piece.color);
        world_set_sort(game->world, game_piece->index, game_piece->piece.sort);
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
    game->starting_position = array_list_init(WORLD_SIZE, free);
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

    if (index == 0)
        return UINT_MAX;
    return positions[rand() % index];
}

game_piece_t choose_random_captured_piece_belonging_to_current(game_t *game)
{
    uint lgt = 0;
    game_piece_t *tab = malloc(sizeof(game_piece_t) * game->captured_pieces_list->len);
    for (uint i = 0; i < game->captured_pieces_list->len; i++)
    {
        game_piece_t *piece = array_list_get(game->captured_pieces_list, i);
        if (piece->piece.color == game->current_player->color)
        {
            tab[lgt++] = *piece;
        }
    }

    if (lgt == 0)
    {
        free(tab);
        game_piece_t res = {.index = UINT_MAX};
        return res;
    }
    uint rand_int = rand() % lgt;
    game_piece_t res = tab[rand_int];

    free(tab);
    return res;
}

int vs_compare_game_piece(void *vp1, void *vp2)
{
    game_piece_t *p1 = vp1;
    game_piece_t *p2 = vp2;

    return !(p1->index == p2->index && p1->piece.color == p2->piece.color && p1->piece.sort && p2->piece.sort);
}

void current_player_try_escape(game_t *game, game_piece_t piece)
{
    if (world_get_sort(game->world, piece.index) == NO_SORT)
    {
        int choice = rand() % 2;
        if (choice == 0)
        {
            if (verbose >= 2)
                printf("Piece of color %u of sort %u revived at pos %u\n", piece.piece.color, piece.piece.sort, piece.index);
            world_set_sort(game->world, piece.index, piece.piece.sort);
            world_set(game->world, piece.index, piece.piece.color);

            int idx = array_list_get_index(game->captured_pieces_list, &piece, vs_compare_game_piece);
            assert(idx != -1);
            game_piece_t *rmv = array_list_remove(game->captured_pieces_list, idx);
            free(rmv);
        }
    }
}

void print_position(void *vpos)
{
    position_t *pos = vpos;
    printf("{%u, %u}\n", pos->col, pos->row);
}

node_t *choose_random_move_for_piece(game_t *game, uint piece)
{
    position_t position;
    position_from_idx(&position, piece);
    node_t *moves = get_moves(game->world, &position, game->starting_position);
    position_t pos;
    position_from_idx(&pos, piece);
    if (verbose >= 2)
        tree_print(moves, print_position);

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

void game_free(game_t *game)
{
    array_list_free(game->captured_pieces_list);
    array_list_free(game->starting_position);
    free(game);
}

void capture_piece_at(game_t *game, uint index)
{
    game_piece_t *piece = malloc(sizeof(game_piece_t));

    piece->index = index;
    piece->piece.color = world_get(game->world, index);
    piece->piece.sort = world_get_sort(game->world, index);

    array_list_push(game->captured_pieces_list, piece);
}

void current_player_move_piece(game_t *game, node_t *move)
{
    node_t *move_tree_root = node_get_root(move);
    uint destination_index = position_to_idx((position_t *)move->value);
    uint source_index = position_to_idx((position_t *)move_tree_root->value);
    enum sort_t source_sort = world_get_sort(game->world, source_index);

    if (world_get_sort(game->world, destination_index) != NO_SORT && source_index != destination_index)
    {
        if (verbose >= 2)
            printf("captured piece at pos %d\n", destination_index);
        capture_piece_at(game, destination_index);
    }

    world_set_sort(game->world, source_index, NO_SORT);
    world_set(game->world, source_index, NO_COLOR);

    world_set(game->world, destination_index, game->current_player->color);
    world_set_sort(game->world, destination_index, source_sort);

    node_free(move_tree_root);

    return;
}

bool check_complex_win(game_t *game)
{
    bool victories[MAX_COLOR];

    for (enum color_t c = 1; c < MAX_COLOR; c++)
    {
        bool victory = true;
        for (uint i = 0; i < game->starting_position->len; i++)
        {
            game_piece_t *piece = array_list_get(game->starting_position, i);
            if (piece->piece.color == c)
            {
                if (world_get_sort(game->world, piece->index) == NO_SORT
                || world_get(game->world, piece->index) == NO_COLOR || world_get(game->world, piece->index) == c)
                {
                    victory = false;
                    break;
                }
            }
        }
        victories[c] = victory;
    }
    for (enum color_t c = 1; c < MAX_COLOR; c++)
    {
        if (victories[c])
            return true;
    }
    return false;
}

bool check_win(game_t *game)
{
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
        return check_complex_win(game);
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