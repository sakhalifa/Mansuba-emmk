#include "neighbors.h"
#include "util.h"

typedef enum {
    SQUARE = 0,
    TRIANGULAR = 1,
    HEXAGONAL = 2
} relation_t;

relation_t current_relation = SQUARE;

void init_neighbors(uint seed){
    if(seed < MAX_RELATIONS){
        current_relation = seed;
    }
}

uint get_neighbor_square(uint idx, enum dir_t d){
    

    uint col = idx%WIDTH;
    uint row = idx/WIDTH;
    
    if (d == NORTH || d == NWEST || d == NEAST) row -= 1;

    if (d == SOUTH || d == SWEST || d == SEAST) row += 1;
    
    if (d == EAST || d == NEAST || d == SEAST) col += 1;

    if (d == WEST || d == NWEST || d == SWEST) col -= 1;


    //if the coordinates are outside the square game grid then it is not a neighbor
    if(col > WIDTH-1 || row > HEIGHT-1) return UINT_MAX;

    return row*WIDTH + col;
}

unsigned int get_neighbor(unsigned int idx, enum dir_t d){
    if (idx >= WORLD_SIZE) return UINT_MAX;
    switch(current_relation){
        case SQUARE:
            return get_neighbor_square(idx, d);
        default:
            return UINT_MAX;
    }
    
}  


struct neighbors_t get_neighbors(unsigned int idx){
    struct neighbors_t neighs;

    uint new_idx;
    uint neighs_index = 0;
    for (int dir = 0; dir < MAX_DIR; dir++)
    {
        int true_dir = dir-4;                        // minus 4 due to the fact that the enum dir minimum is equal to -4
        if(true_dir % 2 == 0) continue; 
        new_idx = get_neighbor(idx, true_dir); 
        if (new_idx != UINT_MAX){
            neighs.n[neighs_index].d = true_dir;
            neighs.n[neighs_index].i = new_idx;
            neighs_index++;
        }

    }
    if (neighs_index == MAX_NEIGHBORS) return neighs;
    
    neighs.n[neighs_index].d = NO_DIR;
    neighs.n[neighs_index].i = UINT_MAX;
    return neighs;
}