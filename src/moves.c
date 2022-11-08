#include "moves.h"
#include "neighbors.h"
#include <limits.h>

int cmp_move_voidstar(void *m1, void *m2)
{
    return cmp_moves((move_t *)m1, (move_t *)m2);
}

void init_move(move_t *ptr_move, int f_idx, int t_idx)
{
    ptr_move->from.col = f_idx % WIDTH;
    ptr_move->from.row = f_idx / WIDTH;
    ptr_move->to.col = t_idx % WIDTH;
    ptr_move->to.row = t_idx / WIDTH;
}

void add_jumps(array_list_t *l, struct world_t *world, struct neighbors_t *neighbors, int start, int idx)
{
    if (start == idx)
    {
        return;
    }
    for (int i = 0; i < MAX_NEIGHBORS && neighbors->n[idx].i != UINT_MAX; i++)
    {
        int n_idx = neighbors->n[idx].i;
        if (world_get_sort(world, n_idx) != NO_SORT)
        {
            add_jump_if_possible(l, world, start, idx, neighbors->n[idx].d);
        }
    }
}

void add_jump_if_possible(array_list_t *l, struct world_t *world, int start, int src, enum dir_t dir)
{
    
    unsigned int dst = get_neighbor(src, dir);
    dst = get_neighbor(dst, dir);
    move_t mv;
    init_move(&mv, src, dst);
    if (dst == UINT_MAX || array_list_contains(l, &mv, cmp_move_voidstar))
    {
        return;
    }
    struct neighbors_t dst_neighbors = get_neighbors(dst);
    add_jumps(l, world, &dst_neighbors, start, dst);
}

void add_simple_moves(array_list_t *l, struct world_t *world, struct neighbors_t *neighbors, int idx)
{
    for (int i = 0; i < MAX_NEIGHBORS && neighbors->n[idx].i != UINT_MAX; i++)
    {
        int n_idx = neighbors->n[idx].i;
        if (world_get_sort(world, n_idx) == NO_SORT)
        {
            move_t *move = malloc(sizeof(move_t));
            init_move(move, idx, n_idx);
            array_list_push(l, move);
        }
        else
        {
            add_jump_if_possible(l, world, idx, idx, neighbors->n[idx].d);
        }
    }
}

array_list_t *get_moves(struct world_t *world, int idx)
{
    array_list_t *l = array_list_init(0, free);
    struct neighbors_t neighbors = get_neighbors(idx);
    add_simple_moves(l, world, &neighbors, idx);

    return l;
}

int cmp_moves(move_t *m1, move_t *m2)
{
    return cmp_positions(&(m1->from), &(m2->from)) && cmp_positions(&(m1->to), &(m2->to));
}