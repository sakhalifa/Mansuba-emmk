#include "game.h"
#include "distance.h"
#include "input.h"
#include <getopt.h>
#include <sys/time.h>

int verbose = 1;

uint read_player_piece(game_t *game){
    printf("Choose your piece\n");

    uint index = read_player_position();
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

node_t * read_player_move(game_t *game, uint piece_index){
    position_t position;
    position_from_idx(&position, piece_index);
    node_t *moves = get_moves(game->world, &position, game->starting_position);
    
    display_game_with_moves(game, moves);
    printf("Chose your move : \n");

    uint index = read_player_position();
    if (index == UINT_MAX) return read_player_move(game, piece_index);
    position_t chosen_position;
    position_from_idx(&chosen_position, index);

    //TODO switch tree print to display row col instead of col row 
    node_t *player_move = tree_get_node(moves, &chosen_position, (void*)cmp_positions);
    if (player_move == NULL) return read_player_move(game, piece_index);

    return player_move;
}


struct game_result game_loop(game_t *game, int verbose)
{
    int winner = -1;
    uint seed = 0;
    while ((winner == -1) && (game->turn < game->max_turns))
    {
        init_neighbors(seed);
        if (verbose >= 1)
            display_game(game);
        if(verbose >= 2)
            printf("Playing as player n°%u, is a bot = %d\n", game->current_player->color, game->current_player->automated);
        int choice = rand() % 2;
        if (game->captured_pieces_list->len == 0 || choice == 0)
        {
            uint piece_idx = game->current_player->automated ? choose_random_piece_belonging_to_current(game) : read_player_piece(game);
            if(verbose >= 2){
                position_t pos_deb;
                position_from_idx(&pos_deb, piece_idx);
                printf("Chose piece at ");
                position_print(&pos_deb);
                printf("\n");
            }
            if (piece_idx != UINT_MAX)
            {
                node_t *move = game->current_player->automated ? choose_best_move_for_piece(game, piece_idx): read_player_move(game, piece_idx);
                if (move != NULL)
                {
                    if(verbose >= 2){
                        printf("Chose move to ");
                        position_print((position_t *)move->value);
                        printf("\n");
                    }
                    current_player_move_piece(game, move);
                }else if(verbose >= 2){
                    printf("Couldn't chose move!\n");
                }
            }
        }
        else
        {
            game_piece_t piece = choose_random_captured_piece_belonging_to_current(game);
            printf("trying to free piece\n");

            if (piece.index != UINT_MAX)
            {
                current_player_try_escape(game, piece);
            }
        }

        if (check_win(game))
            winner = game->current_player->color;
        game->turn++;
        change_player(game, next_player(game->current_player));
        seed = seed + 1;
        seed %= MAX_RELATIONS;
    }
    struct game_result res = {winner, game->turn};
    return res;
}

int main(int argc, char *const *argv)
{
    if(WORLD_SIZE > 50000){
        fprintf(stderr, "Game board too big!");
    }
    init_neighbors(SQUARE);
    
    int max_turn = 2 * WORLD_SIZE;
    struct timeval tv;
    gettimeofday(&tv, NULL);
    long seed = tv.tv_sec * 1000000 + tv.tv_usec;
    enum victory_type victory_type = SIMPLE;
    uint players_number = 0;
    int opt;
    while ((opt = getopt(argc, argv, "t:m:s:v:p:")) != -1)
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
            if (max_turn <= 0)
            {
                fprintf(stderr, "Error, max turns cannot be 0 or less\n");
                exit(EXIT_FAILURE);
            }
            break;
        case 's':
            seed = atoi(optarg);
            break;
        case 'v':
            verbose = atoi(optarg);
            break;

        case 'p':
            players_number = atoi(optarg);
            if (players_number > MAX_PLAYERS)
            {
                fprintf(stderr, "Error, you cannot have more than %d players\n", MAX_PLAYERS);
                exit(EXIT_FAILURE);
            }
            break;
        default:
            fprintf(stderr, "Usage: %s [-t s|c] [-m maxTurns] [-s seed] [-v verbose_level]\n",
                    argv[0]);
            exit(EXIT_FAILURE);
        }
    }
    if (verbose >= 0)
        printf("%ld\n", seed);
    srand(seed);

    struct world_t *world = world_init();
    init_players(players_number);
    player_t *player = get_random_player();
    game_t *game = game_init(world, max_turn, victory_type, player);
    load_starting_position(game);
    init_distance_lookup_table();
    compute_distance_lookup_table(game->starting_position, SQUARE);
    compute_distance_lookup_table(game->starting_position, TRIANGULAR);
    compute_distance_lookup_table(game->starting_position, HEXAGONAL);
    world_populate(game);
    struct game_result game_res = game_loop(game, verbose);

    if (verbose >= 1)
        display_game(game);

    if (verbose >= 0)
    {
        if (game_res.winner != -1)
            printf("Partie gagnée par le joueur %d après %u turns\n", game_res.winner, game_res.turns);
        else
            printf("Ex-aequo en %d tours\n", game_res.turns);
    }
    game_free(game);
    free_distance_lookup_table();
    return EXIT_SUCCESS;
}
