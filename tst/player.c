#include "util.h"
#include "player.h"
#include "geometry.h"

extern player_t players[MAX_PLAYERS];

void test_player_init(void){
    init_players(0);


    for (int i = 0; i < MAX_PLAYERS; i++)
    {
        assert(players[i].color == (unsigned int)NO_COLOR + i + 1);
    }
}

void test_random_player(void){
    init_players(0);
    player_t *p = get_random_player();

    assert(p);
    bool flag = false;
    for (enum color_t c = 1; c < MAX_COLOR; c++)
    {
        if (p->color == c){
            flag = true;
            break;
        }
    }
    
    assert(flag == true);
}


void test_next_player(void){
    init_players(0);

    player_t *p = players;

    assert(p->color == NO_COLOR+1);
    
    p = next_player(p);
    assert(p->color == NO_COLOR+2);

    p = players + MAX_PLAYERS - 1;
    assert(p->color == MAX_COLOR - 1);
    p = next_player(p);
    assert(p->color == NO_COLOR + 1);


}


