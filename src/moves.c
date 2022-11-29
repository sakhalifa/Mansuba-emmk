#include "moves.h"
#include "neighbors.h"
#include "util.h"
#include <stdio.h>

int vs_cmp_pos_pos(void *pos1, void *pos2)
{
    return cmp_positions((position_t *)pos1, (position_t *)pos2);
}

void add_position_if_free(uint pos_idx, struct world_t *world, node_t *node, uint source_index)
{
    if (pos_idx == UINT_MAX) return;
    if (world_get_sort(world, pos_idx) != NO_SORT && world_get(world, pos_idx) == world_get(world, source_index)) return;

    {
        position_t *pos = malloc(sizeof(position_t));
        position_from_idx(pos, pos_idx);
        node_add_child(node, pos);
    }
}

void add_pawn_simple_moves(struct world_t *world, struct neighbors_t *neighbors, node_t *root, uint source_index)
{
    for (int i = 0; i < MAX_NEIGHBORS && neighbors->n[i].i != UINT_MAX; i++)
    {

        unsigned int cur_neighbor = neighbors->n[i].i;
        add_position_if_free(cur_neighbor, world, root, source_index);
    }
}

void add_tower_moves(struct world_t *world, node_t *root){
    for (enum dir_t dir = -4; dir < MAX_DIR-4; dir++)
    {
        if (dir % 2 == 0) continue;

        position_t *position = root->value;
        uint index_neighbor = get_neighbor(position_to_idx(position), dir);

        if (index_neighbor == UINT_MAX) continue;                       //is inside the grid
        if (world_get_sort(world, index_neighbor) != NO_SORT ) continue;// is a free space

        node_t *current = root; 
        while ((index_neighbor != UINT_MAX) && ((world_get_sort(world, index_neighbor) == NO_SORT) || world_get(world,index_neighbor) != world_get(world, position_to_idx(position))))
        {
            position_t *malloc_pos = malloc(sizeof(position_t));
            position_from_idx(malloc_pos, index_neighbor);
            current = node_add_child(current, malloc_pos);

            if (world_get_sort(world, index_neighbor) != NO_SORT){
                return;
            }
            index_neighbor = get_neighbor(index_neighbor, dir);
        }
    }
    
}

void add_pawn_jumps(struct world_t *world, struct neighbors_t *neighbors, node_t *root, uint source_index)
{
    for (int i = 0; i < MAX_NEIGHBORS && neighbors->n[i].i != UINT_MAX; i++)
    {
        unsigned int cur_neighbor = neighbors->n[i].i;
        if (cur_neighbor != UINT_MAX && world_get_sort(world, cur_neighbor) == PAWN)
        {
            unsigned int far_neighbor = get_neighbor(cur_neighbor, neighbors->n[i].d);
            if (far_neighbor != UINT_MAX)
            {
                position_t cur_far_neighbor_pos;
                position_from_idx(&cur_far_neighbor_pos, far_neighbor);
                if (node_has_parent(root, &cur_far_neighbor_pos, vs_cmp_pos_pos))
                    continue;
                position_t *malloc_pos = malloc(sizeof(position_t));
                position_from_idx(malloc_pos, far_neighbor);
                node_t *child = node_add_child(root, malloc_pos);

                if (world_get_sort(world, far_neighbor) != NO_SORT){
                    return;
                }

                struct neighbors_t new_neighbors = get_neighbors(far_neighbor);
                add_pawn_jumps(world, &new_neighbors, child, source_index);
            }
        }
    }
}

void add_elephant_moves(struct world_t *world, node_t *root, uint source_index)
{
    position_t *init_pos = root->value;
    uint init_pos_idx = position_to_idx(init_pos);
    for (int d = 0; d < MAX_DIR; d++)
    {
        enum dir_t true_dir = d - 4;
        if (d % 2 == 0) // Combined directions
        {
            uint pos_idx = get_neighbor(init_pos_idx, true_dir);
            add_position_if_free(pos_idx, world, root, source_index);
        }
        else // Pure directions
        {
            uint pos_idx = get_neighbor(init_pos_idx, true_dir);
            uint far_pos_idx = get_neighbor(pos_idx, true_dir);
            add_position_if_free(pos_idx, world, root, source_index);
            add_position_if_free(far_pos_idx, world, root, source_index);
        }
    }
}

node_t *get_moves(struct world_t *world, position_t *pos)
{
    position_t *malloc_pos = malloc(sizeof(position_t));
    malloc_pos->col = pos->col;
    malloc_pos->row = pos->row;
    uint source_index = position_to_idx(pos);
    node_t *root = tree_create(malloc_pos, free);

    enum sort_t sort = world_get_sort(world, position_to_idx(pos));
    struct neighbors_t neighbors = get_neighbors(position_to_idx(pos));
    switch (sort)
    {
    case PAWN:
        add_pawn_simple_moves(world, &neighbors, root, source_index);
        add_pawn_jumps(world, &neighbors, root, source_index);
        break;
    case ELEPHANT:
        add_elephant_moves(world, root, source_index);
        break;
    case TOWER:
        add_tower_moves(world, root);
        break;
    default:
        break;
    }

    return root;
}