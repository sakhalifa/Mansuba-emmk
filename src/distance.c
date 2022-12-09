#include "util.h"
#include "neighbors.h"
#include "position.h"
#include "linked_list.h"
#include "array_list.h"

unsigned short int *distance_lookup_table = NULL;

void init_distance_lookup_table(array_list_t *starting_pos)
{
    if (distance_lookup_table != NULL)
        free(distance_lookup_table);
    distance_lookup_table = malloc(sizeof(unsigned short int) * WORLD_SIZE * starting_pos->len * MAX_RELATIONS);
}

void compute_distance_lookup_table(array_list_t *starting_pos, relation_t relation){
    
}

unsigned short int get_distance(position_t *from, uint starting_pos_ind)
{
    return *(((distance_lookup_table + get_neighbors_seed() * MAX_RELATIONS * WORLD_SIZE) + position_to_idx(from) * WORLD_SIZE) + starting_pos_ind);
}

void set_distance(unsigned short int value, position_t *from, uint starting_pos_ind)
{
    *(((distance_lookup_table + get_neighbors_seed() * MAX_RELATIONS * WORLD_SIZE) + position_to_idx(from) * WORLD_SIZE) + starting_pos_ind) = value;
}

void free_distance_lookup_table()
{
    free(distance_lookup_table);
}