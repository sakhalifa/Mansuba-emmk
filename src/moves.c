#include "moves.h"
#include "neighbors.h"
#include "util.h"
#include <stdio.h>

void add_simple_moves(struct world_t *world, struct neighbors_t *neighbors, node_t *root)
{
    for (int i = 0; i < MAX_NEIGHBORS && neighbors->n[i].i != UINT_MAX; i++)
    {
        
        unsigned int cur_neighbor = neighbors->n[i].i;
        if (cur_neighbor != UINT_MAX && world_get_sort(world, cur_neighbor) == NO_SORT)
        {
            position_t *malloc_pos = malloc(sizeof(position_t));
            position_from_idx(malloc_pos, cur_neighbor);
            node_add_child(root, malloc_pos);
        }
    }
}

int vs_cmp_pos_pos(void *pos1, void *pos2)
{
    return cmp_positions((position_t *)pos1, (position_t *)pos2);
}

void add_jumps(struct world_t *world, struct neighbors_t *neighbors, node_t *root)
{
    for (int i = 0; i < MAX_NEIGHBORS && neighbors->n[i].i != UINT_MAX; i++)
    {
        unsigned int cur_neighbor = neighbors->n[i].i;
        if (cur_neighbor != UINT_MAX && world_get_sort(world, cur_neighbor) == PAWN)
        {
            unsigned int far_neighbor = get_neighbor(cur_neighbor, neighbors->n[i].d);
            if (far_neighbor != UINT_MAX && world_get_sort(world, far_neighbor) == NO_SORT)
            {
                position_t cur_far_neighbor_pos;
                position_from_idx(&cur_far_neighbor_pos, far_neighbor);
                if (node_has_parent(root, &cur_far_neighbor_pos, vs_cmp_pos_pos))
                    continue;
                position_t *malloc_pos = malloc(sizeof(position_t));
                position_from_idx(malloc_pos, far_neighbor);
                node_t *child = node_add_child(root, malloc_pos);
                struct neighbors_t new_neighbors = get_neighbors(far_neighbor);
                add_jumps(world, &new_neighbors, child);
            }
        }
    }
}

node_t *get_moves(struct world_t *world, position_t *pos)
{
    position_t *malloc_pos = malloc(sizeof(position_t));
    malloc_pos->col = pos->col;
    malloc_pos->row = pos->row;
    node_t *root = tree_create(malloc_pos, free);

    struct neighbors_t neighbors = get_neighbors(position_to_idx(pos));
    add_simple_moves(world, &neighbors, root);
    add_jumps(world, &neighbors, root);

    return root;
}