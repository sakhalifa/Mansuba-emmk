#include <sys/time.h>
#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>
#include "project.h"

uint choose_random_piece_belonging_to(struct world_t *world, player_t *player)
{
    uint positions[WORLD_SIZE];
    uint index = 0;
    for (uint i = 0; i < WORLD_SIZE; i++)
    {
        if (world_get(world, i) == player->color)
        {
            positions[index] = i;
            index++;
        }
    }

    assert(index != 0);
    return positions[rand() % index];
}

node_t *choose_random_move_for_piece(struct world_t *world, uint piece)
{
    position_t position;
    position_from_idx(&position, piece);
    node_t *moves = get_moves(world, &position);

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

void move_piece(struct world_t *world, node_t *move, player_t *player)
{

    world_set(world, position_to_idx((position_t *)move->value), player->color);
    world_set_sort(world, position_to_idx((position_t *)move->value), PAWN);
    while (move->parent != NULL)
    {
        move = move->parent;
    }

    world_set_sort(world, position_to_idx((position_t *)move->value), NO_SORT);
    world_set(world, position_to_idx((position_t *)move->value), NO_COLOR);

    node_free(move);

    return;
}

bool check_win(struct world_t *world, enum victory_type victory_type)
{
    switch (victory_type)
    {
    case SIMPLE:
        for (int i = 0; i < HEIGHT; i++)
        {
            if (world_get(world, (i * WIDTH)) == WHITE)
            {
                return true;
            }
            if (world_get(world, ((i + 1) * WIDTH) - 1) == BLACK)
            {
                return true;
            }
        }
        return false;

    case COMPLEX:
        for (int i = 0; i < HEIGHT; i++)
        {
            if (world_get(world, (i * WIDTH)) != WHITE)
            {
                return false;
            }
            if (world_get(world, ((i + 1) * WIDTH) - 1) != BLACK)
            {
                return false;
            }
        }
        return true;

    default:
        return false;
    }
}

void world_populate(struct world_t *world)
{
    for (int i = 0; i < HEIGHT; i++)
    {
        world_set(world, (i * WIDTH), BLACK);
        world_set_sort(world, (i * WIDTH), PAWN);

        world_set(world, ((i + 1) * WIDTH) - 1, WHITE);
        world_set_sort(world, ((i + 1) * WIDTH) - 1, PAWN);
    }
}

void display_game(struct world_t *world)
{
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
            printf(" %s", place_to_string(world_get(world, i * WIDTH + j), world_get_sort(world, i * WIDTH + j)));
        }
        printf("|\n");
    }

    for (int j = -2; j < WIDTH * 3; j++)
    {
        printf("-");
    }
    printf("\n");
}

struct game_result
{
    int winner;
    uint turns;
};
struct game_result game_loop(struct world_t *world, player_t *player, int max_turns, enum victory_type victory_type)
{
    int winner = -1;
    int turn_counter = 0;
    while ((winner == -1) && (turn_counter < max_turns))
    {
        display_game(world);
        uint piece = choose_random_piece_belonging_to(world, player);

        node_t *move = choose_random_move_for_piece(world, piece);

        if (move != NULL)
        {
            move_piece(world, move, player);
        }

        if (check_win(world, victory_type))
            winner = player->color;
        turn_counter++;
        player = next_player(player);
    }
    struct game_result res = {winner, turn_counter};
    return res;
}

int main(int argc, char *argv[])
{
    int max_turn = 2 * WORLD_SIZE;
    struct timeval tv;
    gettimeofday(&tv, NULL);
    long seed = tv.tv_sec * 1000000 + tv.tv_usec;
    enum victory_type victory_type = SIMPLE;
    int opt;
    while ((opt = getopt(argc, argv, "t:m:s:")) != -1)
    {
        switch (opt)
        {
        case 't':
            switch (optarg[0])
            {
            case 's':
                victory_type = SIMPLE;
                break;
            case 'c':
                victory_type = COMPLEX;
                break;
            default:
                fprintf(stderr, "Usage: %s [-t s|c] [-m maxTurns] [-s seed]\n",
                        argv[0]);
                exit(EXIT_FAILURE);
            }
            break;
        case 'm':
            max_turn = atoi(optarg);
            break;
        case 's':
            seed = atoi(optarg);
            break;
        default: /* aq?aq */
            fprintf(stderr, "Usage: %s [-t s|c] [-m maxTurns] [-s seed]\n",
                    argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    printf("%ld\n", seed);
    srand(seed);

    struct world_t *world = world_init();
    world_populate(world);
    init_players();
    player_t *player = get_random_player();

    struct game_result game_res = game_loop(world, player, max_turn, victory_type);

    display_game(world);

    if (game_res.winner != -1)
        printf("Partie gagnée par le joueur %d après %u turns\n", game_res.winner, game_res.turns);
    else
        printf("Ex-aequo en %d tours\n", game_res.turns);

    return EXIT_SUCCESS;
}