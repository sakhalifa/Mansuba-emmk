#include "util.h"
#include "player.h"

player_t players[MAX_PLAYERS];


player_t *get_random_player(){
    return players + rand()%MAX_PLAYERS;
}

void init_players(uint real_players){

    assert(real_players <= MAX_PLAYERS);
    enum color_t c = NO_COLOR + 1; //taking the first color 
    int idx = 0;
    while ( c < MAX_COLOR)
    {
        assert(idx < MAX_PLAYERS);
        players[idx].color = c;
        c++;
        idx++;
    }

    for (uint i = 0; i < real_players; i++)
    {
        players[i].automated = false;
    }
}

player_t *next_player(player_t *p){
    if (p->color + 1 == MAX_COLOR) return players;
    return players + p->color; 
}
