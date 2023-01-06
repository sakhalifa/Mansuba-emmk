#ifndef __POSITION_H__
#define __POSITION_H__

typedef struct position
{
    unsigned int col;
    unsigned int row;
} position_t;

/// @brief Transforms a position from an index.
/// @param pos the pointer of position to update
/// @param idx the index 
void position_from_idx(position_t *pos, unsigned int idx);

/// @brief Transforms a position to the corresponding index
/// @param pos the position
/// @return the index of the position in the world
unsigned int position_to_idx(position_t *pos);

/// @brief Print on the standard output the position in format "{row,col}"
/// @param p the position
void position_print(position_t *p);

/// @brief Checks if 2 positions are equals
/// @param pos1 1st position
/// @param pos2 2nd position
/// @return True if they are equal, false otherwise
int cmp_positions(position_t *pos1, position_t *pos2);

#endif