#ifndef __POSITION_H__
#define __POSITION_H__

typedef struct position
{
    int col;
    int row;
} position_t;

int cmp_positions(position_t *pos1, position_t *pos2);

#endif