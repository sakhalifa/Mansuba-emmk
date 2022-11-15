#include <assert.h>
#include <stdio.h>
#include "../src/moves.h"
#include "../src/world.h"

void free_nothing(void *_)
{
    _ = _;
}

bool are_trees_equal(node_t *t1, node_t *t2)
{
    position_t *t1_pos = t1->value;
    position_t *t2_pos = t2->value;
    if (cmp_positions(t1_pos, t2_pos))
    {
        printf("Expected {%u,%u} Got {%u,%u}\n", t1_pos->col, t1_pos->row, t2_pos->col, t2_pos->row);
        return false;
    }
    if (t1->children->len != t2->children->len)
    {
        printf("Expected child_length=%ld, Got child_length=%ld\n", t1->children->len, t2->children->len);
        return false;
    }
    for (int i = 0; i < t1->children->len; i++)
    {
        if (!are_trees_equal((node_t *)array_list_get(t1->children, i), (node_t *)array_list_get(t2->children, i)))
        {
            return false;
        }
    }
    return true;
}

position_t two_one = {2, 1};
position_t one_one = {1, 1};
position_t four_one = {4, 1};
position_t four_three = {4, 3};
position_t two_three = {2, 3};

node_t *get_expected_output()
{
    node_t *root = tree_create(&two_one, free_nothing);
    node_t *cur_child = node_add_child(root, &one_one);
    cur_child = node_add_child(root, &two_three);
    cur_child = node_add_child(cur_child, &four_three);
    cur_child = node_add_child(cur_child, &four_one);
    cur_child = node_add_child(root, &four_one);
    cur_child = node_add_child(cur_child, &four_three);
    cur_child = node_add_child(cur_child, &two_three);

    return root;
}

void test_moves()
{
    struct world_t *world = world_init();
    position_t pos[] = {{2, 0}, {2, 2}, {3, 1}, {3, 3}, {4, 2}};
    for (int i = 0; i < 5; i++)
    {
        world_set_sort(world, position_to_idx(pos + i), PAWN);
    }
    position_t starting_position = {2, 1};
    node_t *move_tree = get_moves(world, &starting_position);
    node_t *expected_output = get_expected_output();
    assert(are_trees_equal(expected_output, move_tree));

    node_free(move_tree);
    node_free(expected_output);
}