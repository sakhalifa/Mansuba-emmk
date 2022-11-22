#ifndef __POSITION_H__
#define __POSITION_H__

typedef struct position
{
    unsigned int col;
    unsigned int row;
} position_t;

void position_from_idx(position_t *pos, unsigned int idx);
unsigned int position_to_idx(position_t *pos);

void position_print(position_t *p);

int cmp_positions(position_t *pos1, position_t *pos2);

#endif