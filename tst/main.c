#include "main.h"


int main(){
    test_get_neighbors_square();
    test_get_neighbors_triangle();
    test_get_neighbor();
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
    return 0;
}