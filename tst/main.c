#include "main.h"

int verbose = 2;

int main(){
    test_get_neighbor();
    test_get_neighbors();
    printf("Finished testing neighbors.c\n");

    test_array();
    printf("Finished testing array_list.c\n");

    test_moves();
    printf("Finished testing moves.c\n");

    test_trees();
    printf("Finished testing trees.c\n");

    test_player_init();
    // test_random_player();
    // test_next_player();
    printf("Finished testing player.c\n");

    test_game();
    printf("Finished testing game.c\n");

    test_distance();
    printf("Finished testing distance.c\n");
    return 0;
}