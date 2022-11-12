#include "position.h"
#include "geometry.h"


int cmp_positions(position_t *pos1, position_t *pos2){
    return pos1->col == pos2->col && pos1->row == pos2->row;
}

void position_from_idx(position_t *pos, int idx){
    pos->col = idx % WIDTH;
    pos->row = idx / WIDTH;
}

int position_to_idx(position_t *pos){
    return pos->row * WIDTH + pos->col;
}