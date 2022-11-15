#include "util.h"
#include "world.h"
#include "player.h"
#include <time.h>

int main(){
    srand(time(NULL));

    struct world_t *w = world_init();
    init_players();
    player_t *p = get_random_player();
    printf("%d\n", p->color);

    

    printf("hello \n");
    return EXIT_SUCCESS;
}