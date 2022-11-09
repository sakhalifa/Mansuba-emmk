#include "neighbors.h"
#include "util.h"

unsigned int get_neighbor(unsigned int idx, enum dir_t d){
    if (d == NO_DIR || idx >= WORLD_SIZE) return UINT_MAX;

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


struct neighbors_t get_neighbors(unsigned int idx){
    struct neighbors_t neighs;

    uint new_idx;
    uint neighs_index = 0;
    for (int dir = 0; dir < MAX_DIR; dir++)
    {
        new_idx = get_neighbor(idx, dir-4);  // minus 4 due to the fact that the enum dir minimum is equal to -4 
        if (new_idx != UINT_MAX){
            neighs.n[neighs_index].d = dir-4;
            neighs.n[neighs_index].i = new_idx;
            neighs_index++;
        }

    }
    if (neighs_index == MAX_NEIGHBORS) return neighs;
    
    neighs.n[neighs_index].d = NO_DIR;
    neighs.n[neighs_index].i = UINT_MAX;
    return neighs;
}