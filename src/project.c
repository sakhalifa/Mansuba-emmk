#include <stdio.h>
#include "world.h"


int main(int argc, char *argv[])
{
    struct world_t *w = world_init();
    // init_neighbors(0);*

    current_player = get_random_player();
    while (!game_won(w)):
        p = choose_random_piece_belonging_to(w, current_player);
        m = choose_random_move_for_piece(w, p);
        move_piece(w, m);
        current_player = next_player(current_player);

    
    return 0;
}