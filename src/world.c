#include "world.h"
#include "neighbors.h"
#include "util.h"

bool world_initialized = false;
struct world_t world;


struct world_t {
    piece_t pieces[WORLD_SIZE];
};

enum color_t world_get(const struct world_t* world, unsigned int idx){
    assert(idx < WORLD_SIZE);
    return world->pieces[idx].color;
}

void world_set(struct world_t* world, unsigned int idx, enum color_t color){
    assert(idx < WORLD_SIZE);
    world->pieces[idx].color = color;
}


enum sort_t world_get_sort(const struct world_t* world, unsigned int idx){
    assert(idx < WORLD_SIZE);
    return world->pieces[idx].sort;
}


void world_set_sort(struct world_t* world, unsigned int idx, enum sort_t sort){
    assert(idx < WORLD_SIZE);
    world->pieces[idx].sort = sort;
}

struct world_t* world_init(void){
    for (int i = 0; i < WORLD_SIZE; i++)
    {
        world.pieces[i].color = NO_COLOR;
        world.pieces[i].sort = NO_SORT;
    }
    
    world_initialized = true;
    return &world; 
}



