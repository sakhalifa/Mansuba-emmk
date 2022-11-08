#include "world.h"
#include <stdlib.h>
#include <stdbool.h>

struct world_t {
    enum sort_t sort_array[WORLD_SIZE];
    enum color_t color_array[WORLD_SIZE];
};

enum color_t world_get(const struct world_t* b, unsigned int idx){
    return b->color_array[idx];
}

void world_set(struct world_t* b, unsigned int idx, enum color_t c){
    b->color_array[idx] = c;
}


enum sort_t world_get_sort(const struct world_t* b, unsigned int idx){
    return b->sort_array[idx];
}


void world_set_sort(struct world_t* b, unsigned int idx, enum sort_t c){
    b->sort_array[idx] = c;
}





