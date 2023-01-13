#include "util.h"
#include "neighbors.h"
#include "position.h"
#include "linked_list.h"
#include "array_list.h"
#include "distance.h"
#include <string.h>
#define _LOOKUP_TABLE_SIZE (WORLD_SIZE * (MAX_COLOR - 1) * MAX_RELATIONS)

unsigned short *distance_lookup_table = NULL;

void init_distance_lookup_table(void)
{
    if (distance_lookup_table != NULL)
        free(distance_lookup_table);
    distance_lookup_table = malloc(sizeof(unsigned short) * _LOOKUP_TABLE_SIZE);
    CHECK_MALLOC(distance_lookup_table);
    memset(distance_lookup_table, UCHAR_MAX, sizeof(unsigned short) * _LOOKUP_TABLE_SIZE);
}

unsigned short get_distance(relation_t relation, enum color_t color, position_t *from)
{
    uint index = position_to_idx(from);
    if (relation > MAX_RELATIONS || color > MAX_COLOR || index > WORLD_SIZE)
    {
        fprintf(stderr, "Warning, OOB access at %s:%u\n", __FILE__, __LINE__);
        return USHRT_MAX;
    }
    return *(((distance_lookup_table + relation * WORLD_SIZE * (MAX_COLOR - 1)) + (color - 1) * WORLD_SIZE + position_to_idx(from)));
}

void set_distance(unsigned short int value, relation_t relation, enum color_t color, uint index)
{
    if (relation > MAX_RELATIONS || color > MAX_COLOR || index > WORLD_SIZE)
    {
        fprintf(stderr, "Warning, OOB access at %s:%u\n", __FILE__, __LINE__);
        return;
    }
    *(((distance_lookup_table + relation * WORLD_SIZE * (MAX_COLOR - 1)) + (color - 1) * WORLD_SIZE + index)) = value;
}

void init_queue(linked_list_t *queue, const array_list_t *starting_pos, relation_t relation, enum color_t color)
{
    for (uint i = 0; i < array_list_length(starting_pos); i++)
    {
        game_piece_t *game_piece = array_list_get(starting_pos, i);
        if (game_piece->piece.color == color)
        {
            uint *malloced = malloc(sizeof(uint));
            *malloced = game_piece->index;
            linked_list_queue(queue, malloced);
            set_distance(0, relation, color, game_piece->index);
        }
    }
}

void do_bfs(linked_list_t *queue, relation_t relation, enum color_t color)
{
    uint *idx;
    while ((idx = linked_list_get_last(queue)))
    {
        position_t src_pos;
        position_from_idx(&src_pos, *idx);
        unsigned short src_dist = get_distance(relation, color, &src_pos);
        struct neighbors_t neighbors = get_neighbors(*idx);

        for (int i = 0; i < MAX_NEIGHBORS && neighbors.n[i].i != UINT_MAX; i++)
        {
            uint cur_neighbor = neighbors.n[i].i;
            position_t cur_pos;
            position_from_idx(&cur_pos, cur_neighbor);

            unsigned short dest_dist = get_distance(relation, color, &cur_pos);
            if (src_dist + 1 < dest_dist)
            {
                set_distance(src_dist + 1, relation, color, cur_neighbor);
                uint *malloced = malloc(sizeof(int));
                *malloced = cur_neighbor;
                linked_list_queue(queue, malloced);
            }
        }

        linked_list_remove_last(queue);
    }
}

void compute_distance_lookup_table(const array_list_t *starting_pos, relation_t relation)
{
    relation_t old_rel = get_neighbors_seed();
    init_neighbors(relation);
    for (enum color_t color = NO_COLOR + 1; color < MAX_COLOR; color++)
    {
        linked_list_t *queue = linked_list_create(free);
        init_queue(queue, starting_pos, relation, color);
        do_bfs(queue, relation, color);
        linked_list_free(queue);
    }
    init_neighbors(old_rel);
}

void free_distance_lookup_table(void)
{
    free(distance_lookup_table);
}