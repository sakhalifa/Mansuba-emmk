#include "game.h"
#include <getopt.h>
#include <sys/time.h>

struct game_result game_loop(game_t* game)
{
    int winner = -1;
    uint turn_counter = 0;
    uint seed = 0;
    while ((winner == -1) && (turn_counter < game->max_turns))
    {
        init_neighbors(seed);
        display_game(game);
        uint piece = choose_random_piece_belonging_to_current(game);

        node_t *move = choose_random_move_for_piece(game, piece);

        if (move != NULL)
        {
            current_player_move_piece(game, move);
        }

        if (check_win(game))
            winner = game->current_player->color;
        turn_counter++;
        change_player(game, next_player(game->current_player));
        seed = seed + 1;
        seed %= MAX_RELATIONS;
    }
    struct game_result res = {winner, turn_counter};
    return res;
}

int main(int argc, char *const *argv)
{
    init_neighbors(SQUARE);   
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
            if(max_turn <= 0){
                fprintf(stderr, "Error, max turns cannot be 0 or less\n");
                exit(EXIT_FAILURE);
            }
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
    init_players();
    player_t *player = get_random_player();
    game_t game = game_init(world, max_turn, victory_type, player);
    struct game_result game_res = game_loop(&game);

    display_game(&game);

    if (game_res.winner != -1)
        printf("Partie gagnée par le joueur %d après %u turns\n", game_res.winner, game_res.turns);
    else
        printf("Ex-aequo en %d tours\n", game_res.turns);

    return EXIT_SUCCESS;
    return 0;
}
