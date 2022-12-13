#include "game.h"
#include "distance.h"
#include <getopt.h>
#include <sys/time.h>

int verbose = 1;

struct game_result game_loop(game_t *game, int verbose)
{
    int winner = -1;
    uint seed = 0;
    while ((winner == -1) && (game->turn < game->max_turns))
    {
        // init_neighbors(seed);
        if (verbose >= 1)
            display_game(game);
        if(verbose >= 2)
            printf("Playing as player n°%u\n", game->current_player->color);
        int choice = rand() % 2;
        if (game->captured_pieces_list->len == 0 || choice == 0)
        {
            uint piece_idx = choose_random_piece_belonging_to_current(game);
            if(verbose >= 2){
                position_t pos_deb;
                position_from_idx(&pos_deb, piece_idx);
                printf("Chose piece at ");
                position_print(&pos_deb);
                printf("\n");
            }
            if (piece_idx != UINT_MAX)
            {
                node_t *move = choose_best_move_for_piece(game, piece_idx);
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
    int opt;
    while ((opt = getopt(argc, argv, "t:m:s:v:")) != -1)
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
    init_players();
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
