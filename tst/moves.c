#include <assert.h>
#include <stdio.h>
#include "../src/moves.h"
#include "../src/world.h"

void test_moves()
{
    struct world_t *world = world_init();
    position_t pos[] = {{2, 0}, {2, 2}, {3, 1}, {3, 3}, {4, 2}};
    for(int i = 0; i<5; i++){
        world_set_sort(world, position_to_idx(pos+i), PAWN);
    }
    position_t starting_position = {2,1};
    node_t* move_tree = get_moves(world, &starting_position);
    printf("%d\n", move_tree->children->len);
    assert(move_tree->children->len == 3);

    node_free(move_tree);

}