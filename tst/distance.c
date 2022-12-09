#include "util.h"
#include "distance.h"
#include "neighbors.h"
#include "geometry.h"
#include "game.h"
#include <assert.h>
#include <stdio.h>

bool test_distance()
{
    init_neighbors(SQUARE);
    init_distance_lookup_table();
    for (uint i = 0; i < WORLD_SIZE; i++)
    {
        position_t pos;
        position_from_idx(&pos, i);
        for (enum color_t color = 1; color < MAX_COLOR; color++)
        {
            for (relation_t relation = 0; relation < MAX_RELATIONS; relation++)
            {
                assert(get_distance(relation, color, &pos) == USHRT_MAX);
            }
        }
    }

    struct world_t *world = world_init();
    init_players();
    player_t *player = get_random_player();
    game_t *game = game_init(world, 10, SIMPLE, player);
    load_starting_position(game);
    compute_distance_lookup_table(game->starting_position, SQUARE);
    int expected[MAX_COLOR-1][WORLD_SIZE];
    for (enum color_t color = 1; color < MAX_COLOR; color++)
    {
        int cpt = (color == 1 ? 0 : 4);
        for(int i = 0; i<WORLD_SIZE; i++){
            expected[color-1][i] = cpt % 5;
            cpt += (color == 1 ? 1 : 4);
        }
    }
    for (enum color_t color = 1; color < MAX_COLOR; color++)
    {
        for(int i = 0; i<WORLD_SIZE; i++){
            position_t pos;
            position_from_idx(&pos, i);
            assert(get_distance(SQUARE, color, &pos) == expected[color-1][i]);
        }
    }

    free_distance_lookup_table();
    game_free(game);
    return true;
}