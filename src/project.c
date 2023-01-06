#include "game.h"
#include "distance.h"
#include "configuration.h"
#include <string.h>
#include "player_handler.h"
#include <getopt.h>
#include <sys/time.h>
#define MAX_WORLD_SIZE (500 * 100)
#define USAGE_STRING "Usage: %s [-t s|c] [-m maxTurns] [-s seed] [-v verbose_level] [-p number_of_players]\n"

int verbose = 1;

struct game_result game_loop(game_t *game, int verbose)
{
    enum color_t winner = NO_COLOR;
    while ((winner == NO_COLOR) && (game->turn < game->max_turns))
    {
        // init_neighbors(seed);
        if (verbose >= 1)
            display_game(game);
        if (verbose >= 2)
            printf("Playing as player n°%u, is a bot = %d\n", game->current_player->color, game->current_player->automated);
        enum actions choice = game->current_player->automated ? (enum actions)(rand() % MAX_ACTION) : get_player_action(game);
        if (choice == WAIT)
        {
            choice = choice;
        }
        else if (!has_piece_captured(game, game->current_player) || choice == MOVE)
        {
            uint piece_idx = game->current_player->automated ? choose_random_piece_for_player(game, game->current_player) : read_player_piece(game);
            if (verbose >= 2)
            {
                position_t pos_deb;
                position_from_idx(&pos_deb, piece_idx);
                printf("Chose piece at ");
                position_print(&pos_deb);
                printf("\n");
            }
            if (piece_idx != UINT_MAX)
            {
                node_t *move = game->current_player->automated ? choose_best_move_for_piece(game, piece_idx) : get_player_move(game, piece_idx);
                if (move != NULL)
                {
                    if (verbose >= 2)
                    {
                        printf("Chose move to ");
                        position_print((position_t *)move->value);
                        printf("\n");
                    }
                    current_player_move_piece(game, move);
                }
                else if (verbose >= 2)
                {
                    printf("Couldn't chose move!\n");
                }
            }
        }
        else if (choice == ESCAPE)
        {
            game_piece_t piece = game->current_player->automated ? choose_random_captured_piece_for_player(game, game->current_player) : get_player_captured_piece(game, game->current_player);

            if (piece.index != UINT_MAX)
            {
                bool success = current_player_try_escape(game, piece);
                if (success && verbose >= 1)
                {
                    position_t escaped_pos;
                    position_from_idx(&escaped_pos, piece.index);
                    printf("Escape successful at %u,%u\n", escaped_pos.row, escaped_pos.col);
                }
                else if (verbose >= 1)
                {
                    printf("Escape failed\n");
                }
            }
        }

        if (check_win(game))
            winner = game->current_player->color;
        game->turn++;
        change_player(game, next_player(game->current_player));
    }
    struct game_result res = {winner, game->turn};
    return res;
}

void init_default_config()
{
    enable_move_type(SIMPLE_MOVE);
    enable_move_type(SIMPLE_JUMP);
    enable_move_type(MULTIPLE_JUMP);

    add_allowed_sort(PAWN);
    add_allowed_sort(TOWER);
    add_allowed_sort(ELEPHANT);

    set_capture_allowed(true);
    set_relation(SQUARE);
}

void init_dame_chinoises_config()
{
    add_allowed_sort(PAWN);
    enable_move_type(SIMPLE_MOVE);
    enable_move_type(SIMPLE_JUMP);
    enable_move_type(MULTIPLE_JUMP);
    set_relation(HEXAGONAL);
    set_capture_allowed(false);
}

long get_current_time_microseconds()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    long time = tv.tv_sec * 1000000 + tv.tv_usec;
    return time;
}

void print_usage(FILE *buffer, char *binary_name)
{
    fprintf(buffer, USAGE_STRING, binary_name);
}

struct args_config
{
    long seed;
    enum victory_type victory_type;
    uint player_number;
    int max_turn;
    void (*init_config)();
};

struct args_config get_args(int argc, char *const *argv)
{
    struct args_config args = {
        .max_turn = 2 * WORLD_SIZE,
        .seed = get_current_time_microseconds(),
        .victory_type = SIMPLE,
        .player_number = 0,
        .init_config = init_default_config,
    };
    int opt;
    while ((opt = getopt(argc, argv, "t:m:s:v:c:p:")) != -1)
    {
        switch (opt)
        {
        case 't':
            switch (optarg[0])
            {
            case 's':
                args.victory_type = SIMPLE;
                break;
            case 'c':
                args.victory_type = COMPLEX;
                break;
            default:
                print_usage(stderr, argv[0]);
                exit(EXIT_FAILURE);
            }
            break;
        case 'm':
            args.max_turn = atoi(optarg);
            if (args.max_turn <= 0)
            {
                fprintf(stderr, "Error, max turns cannot be 0 or less\n");
                print_usage(stderr, argv[0]);
                exit(EXIT_FAILURE);
            }
            break;
        case 's':
            args.seed = atoi(optarg);
            break;
        case 'v':
            verbose = atoi(optarg);
            break;
        case 'c':
            if (!strcmp(optarg, "dame-chinoises"))
            {
                args.init_config = init_dame_chinoises_config;
            }
            break;

        case 'p':
            args.player_number = atoi(optarg);
            if (args.player_number > MAX_PLAYERS)
            {
                fprintf(stderr, "Error, you cannot have more than %d players\n", MAX_PLAYERS);
                print_usage(stderr, argv[0]);
                exit(EXIT_FAILURE);
            }
            break;
        default:
            print_usage(stderr, argv[0]);
            exit(EXIT_FAILURE);
        }
    }
    return args;
}

int main(int argc, char *const *argv)
{
    if (WORLD_SIZE > MAX_WORLD_SIZE)
    {
        fprintf(stderr, "Game board too big!");
    }
    init_neighbors(SQUARE);

    struct args_config args = get_args(argc, argv);

    if (verbose >= 0)
        printf("%ld\n", args.seed);
    srand(args.seed);

    args.init_config();
    lock_config();
    struct world_t *world = world_init();
    init_players(args.player_number);
    player_t *player = get_random_player();
    game_t *game = game_init(world, args.max_turn, args.victory_type, player);
    load_starting_position(game);
    init_distance_lookup_table();
    compute_distance_lookup_table(game->starting_position, SQUARE);
    compute_distance_lookup_table(game->starting_position, TRIANGULAR);
    compute_distance_lookup_table(game->starting_position, HEXAGONAL);
    world_populate(game);
    init_neighbors(get_relation());
    struct game_result game_res = game_loop(game, verbose);

    if (verbose >= 1)
        display_game(game);

    if (verbose >= 0)
    {
        if (game_res.winner != NO_COLOR)
            printf("Partie gagnée par le joueur %c après %u turns\n", color_to_char(game_res.winner), game_res.turns);
        else
            printf("Ex-aequo en %d tours\n", game_res.turns);
    }
    game_free(game);
    free_distance_lookup_table();
    config_free();
    return EXIT_SUCCESS;
}
