#include "main.h"
#include "configuration.h"
#include "moves.h"

int verbose = 2;

int main(void){
    enable_move_type(SIMPLE_MOVE);
    enable_move_type(SIMPLE_JUMP);
    enable_move_type(MULTIPLE_JUMP);

    add_allowed_sort(PAWN);
    add_allowed_sort(TOWER);
    add_allowed_sort(ELEPHANT);

    set_capture_allowed(true);
    set_relation(SQUARE);
    test_get_neighbor();
    test_get_neighbors();
    printf("Finished testing neighbors.c\n");

    test_array();
    printf("Finished testing array_list.c\n");

    // test_moves();
    // printf("Finished² testing moves.c\n");

    test_trees();
    printf("Finished testing trees.c\n");

    // test_player_init();
    // test_random_player();
    // test_next_player();
    // printf("Finished testing player.c\n");

    test_game();
    printf("Finished testing game.c\n");

    test_distance();
    printf("Finished testing distance.c\n");

    config_free();
    return 0;
}