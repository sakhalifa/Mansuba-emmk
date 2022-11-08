#include "position.h"


int cmp_positions(position_t *pos1, position_t *pos2){
    return pos1->col == pos2->col && pos1->row == pos2->row;
}