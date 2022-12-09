#ifndef __DISTANCE_H__
#define __DISTANCE_H__
#include "array_list.h"
#include "position.h"
#include "util.h"

void init_distance_lookup_table();
void compute_distance_lookup_table(array_list_t *starting_pos, relation_t relation);
unsigned short get_distance(relation_t relation, enum color_t color, position_t *from);
void free_distance_lookup_table();


#endif // __DISTANCE_H__

