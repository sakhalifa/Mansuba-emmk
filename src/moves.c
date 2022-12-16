#include "moves.h"
#include "neighbors.h"
#include "util.h"
#include "configuration.h"
#include <stdio.h>

int vs_cmp_pos_pos(void *pos1, void *pos2)
{
    return cmp_positions((position_t *)pos1, (position_t *)pos2);
}

int vs_cmp_index_game_piece(void *index, void *game_piece)
{
    return !(((game_piece_t *)game_piece)->index == *((uint *)index));
}

void add_position_if_not_start_pos(uint pos_idx, struct world_t *world, node_t *node, uint source_index, array_list_t *starting_pos)
{
    if (pos_idx == UINT_MAX)
        return;
    if (pos_idx == source_index)
        return;
    if (world_get_sort(world, pos_idx) != NO_SORT 
        && (array_list_contains(starting_pos, &pos_idx, vs_cmp_index_game_piece) 
            || world_get(world, pos_idx) == world_get(world, source_index)
            || !is_capture_allowed()))
        return;

    position_t *pos = malloc(sizeof(position_t));
    CHECK_MALLOC(pos);
    position_from_idx(pos, pos_idx);
    node_add_child(node, pos);
}

void add_pawn_simple_moves(struct world_t *world, node_t *root, uint source_index, array_list_t *starting_pos)
{
    struct neighbors_t neighbors = get_neighbors(source_index);
    for (int i = 0; i < MAX_NEIGHBORS && neighbors.n[i].i != UINT_MAX; i++)
    {
        unsigned int cur_neighbor = neighbors.n[i].i;
        add_position_if_not_start_pos(cur_neighbor, world, root, source_index, starting_pos);
    }
}

void add_tower_moves(struct world_t *world, node_t *root, uint source_index, array_list_t *starting_pos)
{
    uint source_idx = position_to_idx((position_t *)root->value);
    for (enum dir_t dir = -4; dir < MAX_DIR - 4; dir++)
    {
        if (dir % 2 == 0)
            continue;

        position_t *position = root->value;
        uint index_neighbor = get_neighbor(position_to_idx(position), dir);

        if (index_neighbor == UINT_MAX)
            continue; // is inside the grid

        node_t *current = root;
        while ((index_neighbor != UINT_MAX) 
        && !(world_get_sort(world, index_neighbor) != NO_SORT
            && (array_list_contains(starting_pos, &index_neighbor, vs_cmp_index_game_piece) 
                || world_get(world, index_neighbor) == world_get(world, source_idx
                || !is_capture_allowed())
                )
            )
        )
        {
            position_t *malloc_pos = malloc(sizeof(position_t));
            CHECK_MALLOC(malloc_pos);
            position_from_idx(malloc_pos, index_neighbor);
            current = node_add_child(current, malloc_pos);

            if (world_get_sort(world, index_neighbor) != NO_SORT)
            {
                break;
            }
            index_neighbor = get_neighbor(index_neighbor, dir);
        }
    }
}



void add_pawn_jumps(struct world_t *world, node_t *root, uint source_index, array_list_t *starting_pos, bool recurse)
{
    struct neighbors_t neighbors = get_neighbors(source_index);
    for (int i = 0; i < MAX_NEIGHBORS && neighbors.n[i].i != UINT_MAX; i++)
    {
        unsigned int cur_neighbor = neighbors.n[i].i;
        if (cur_neighbor != UINT_MAX && world_get_sort(world, cur_neighbor) != NO_SORT)
        {
            unsigned int far_neighbor = get_neighbor(cur_neighbor, neighbors.n[i].d);
            if (far_neighbor != UINT_MAX && !(world_get_sort(world, far_neighbor) != NO_SORT && array_list_contains(starting_pos, &far_neighbor, vs_cmp_index_game_piece)))
            {
                position_t cur_far_neighbor_pos;
                position_from_idx(&cur_far_neighbor_pos, far_neighbor);
                if (node_has_parent(root, &cur_far_neighbor_pos, vs_cmp_pos_pos)
                    || node_has_child(root, &cur_far_neighbor_pos, vs_cmp_pos_pos))
                    continue;
                position_t *malloc_pos = malloc(sizeof(position_t));
                CHECK_MALLOC(malloc_pos);
                position_from_idx(malloc_pos, far_neighbor);
                if (world_get_sort(world, far_neighbor) != NO_SORT && !is_capture_allowed())
                {
                    return;
                }
                node_t *child = node_add_child(root, malloc_pos);
                if (recurse && world_get_sort(world, far_neighbor) != NO_SORT)
                {
                    add_pawn_jumps(world, child, far_neighbor, starting_pos, recurse);
                }
            }
        }
    }
}

void add_pawn_simple_jumps(struct world_t *world, node_t *root, uint source_index, array_list_t *starting_pos){
    add_pawn_jumps(world, root, source_index, starting_pos, false);
}

void add_pawn_multiple_jumps(struct world_t *world, node_t *root, uint source_index, array_list_t *starting_pos){
    add_pawn_jumps(world, root, source_index, starting_pos, true);
}

void add_elephant_moves(struct world_t *world, node_t *root, uint source_index, array_list_t *starting_pos)
{
    position_t *init_pos = root->value;
    uint init_pos_idx = position_to_idx(init_pos);
    for (int d = 0; d < MAX_DIR; d++)
    {
        enum dir_t true_dir = d - 4;
        uint pos_idx = get_neighbor(init_pos_idx, true_dir);
        add_position_if_not_start_pos(pos_idx, world, root, source_index, starting_pos);

        if (d % 2 != 0) // Pure directions
        {
            uint far_pos_idx = get_neighbor(pos_idx, true_dir);
            add_position_if_not_start_pos(far_pos_idx, world, root, source_index, starting_pos);
        }
    }
}

node_t *get_moves(struct world_t *world, position_t *pos, array_list_t *starting_pos)
{
    position_t *malloc_pos = malloc(sizeof(position_t));
    CHECK_MALLOC(malloc_pos);
    malloc_pos->col = pos->col;
    malloc_pos->row = pos->row;
    uint source_index = position_to_idx(pos);
    node_t *root = tree_create(malloc_pos, free);

    enum sort_t sort = world_get_sort(world, position_to_idx(pos));
    array_list_t *allowed_moves = get_allowed_moves_for_sort(sort);
    for(uint i = 0; i<allowed_moves->len; i++){
        ((move_t)array_list_get(allowed_moves, i))(world, root, source_index, starting_pos);
    }

    return root;
}

void enable_move_type(move_type_t move_type){
    switch(move_type){
        case SIMPLE_MOVE:
            add_allowed_move_for_sort(add_pawn_simple_moves, PAWN);
            add_allowed_move_for_sort(add_tower_moves, TOWER);
            add_allowed_move_for_sort(add_elephant_moves, ELEPHANT);
            break;
        case SIMPLE_JUMP:
            add_allowed_move_for_sort(add_pawn_simple_jumps, PAWN);
            break;
        case MULTIPLE_JUMP:
            add_allowed_move_for_sort(add_pawn_multiple_jumps, PAWN);
            break;
        default:
            break;
    }
}