#include "neighbors.h"
#include "util.h"
#include "position.h"

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

uint get_neighbor_triangle(uint idx, enum dir_t d){

    uint col = idx%WIDTH;
    uint row = idx/WIDTH;

    if ((col+row)%2 == 0){
        if(d == SOUTH) row += 1;
        else if (d == WEST) col -= 1;
        else if (d == EAST) col += 1;
        else return UINT_MAX;
    }else{
        if(d == NORTH) row -= 1; 
        else if (d == WEST) col -= 1;
        else if (d == EAST) col += 1;
        else return UINT_MAX;
    }
 
    if(col > WIDTH-1 || row > HEIGHT-1) return UINT_MAX;
    
    return row*WIDTH + col;
}

int compute_hexagonal_offset(position_t *cur_pos,enum dir_t d){
    switch(d){
        case SEAST:
        case NEAST:
            if(cur_pos->row % 2 == 0){
                return 0;
            }else{
                return 1;
            }
        case SWEST:
        case NWEST:
            if(cur_pos->row % 2 == 0){
                return -1;
            }else{
                return 0;
            }
    }
    return 0;
}

uint get_neighbor_hexagonal(uint idx, enum dir_t d){
    if(d == NO_DIR || d == EAST || d == WEST) return idx;
    position_t cur_pos;
    position_from_idx(&cur_pos, idx);
    switch (d)
    {
    case WEST:
        cur_pos.col -= 1;
        break;
    case EAST:
        cur_pos.col += 1;
        break;
    case NEAST:
    case NWEST:
        cur_pos.col += compute_hexagonal_offset(&cur_pos, d);
        cur_pos.row -= 1;
        break;
    case SEAST:
    case SWEST:
        cur_pos.col += compute_hexagonal_offset(&cur_pos, d);
        cur_pos.row += 1;
        break;
    default:
        break;
    }

    if(cur_pos.col >= WIDTH || cur_pos.row >= HEIGHT) return UINT_MAX;
    return position_to_idx(&cur_pos);
}

unsigned int get_neighbor(unsigned int idx, enum dir_t d){
    if (idx >= WORLD_SIZE) return UINT_MAX;
    switch(current_relation){
        case SQUARE:
            return get_neighbor_square(idx, d);
        case HEXAGONAL:
            return get_neighbor_hexagonal(idx, d);
        case TRIANGULAR:
            return get_neighbor_triangle(idx, d);
        default:
            return UINT_MAX;
    }
    
}  


struct neighbors_t get_neighbors(unsigned int idx){
    struct neighbors_t neighs;

    uint new_idx;
    uint neighs_index = 0;
    for (int dir = -4; dir < MAX_DIR-4; dir++) // minus 4 due to the fact that the enum dir minimum is equal to -4
    {
        if(dir % 2 == 0) continue; 
        new_idx = get_neighbor(idx, dir);
        if (new_idx != UINT_MAX){
            neighs.n[neighs_index].d = dir;
            neighs.n[neighs_index].i = new_idx;
            neighs_index++;
        }

    }
    if (neighs_index == MAX_NEIGHBORS) return neighs;
    
    neighs.n[neighs_index].d = NO_DIR;
    neighs.n[neighs_index].i = UINT_MAX;
    return neighs;
}