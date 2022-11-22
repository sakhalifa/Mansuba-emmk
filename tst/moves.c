#include <assert.h>
#include <stdio.h>
#include "../src/moves.h"
#include "../src/world.h"
#include "../src/geometry.h"

void free_nothing(void *_)
{
    _ = _;
}

void display_game(struct world_t *world)
{
    for (int j = -2; j < WIDTH * 3; j++)
    {
        printf("-");
    }
    printf("\n");

    for (int i = 0; i < HEIGHT; i++)
    {
        printf("|");
        for (int j = 0; j < WIDTH; j++)
        {
            printf(" %s", place_to_string(world_get(world, i * WIDTH + j), world_get_sort(world, i * WIDTH + j)));
        }
        printf("|\n");
    }

    for (int j = -2; j < WIDTH * 3; j++)
    {
        printf("-");
    }
    printf("\n");
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
    for (int i = 0; i < (int)t1->children->len; i++)
    {
        if (!are_trees_equal((node_t *)array_list_get(t1->children, i), (node_t *)array_list_get(t2->children, i)))
        {
            return false;
        }
    }
    return true;
}

position_t all_pos[WIDTH][HEIGHT];

node_t *get_expected_output_test_pawn()
{
    /*
    Order:
    south
    west
    east
    north
    */
    node_t *root = tree_create(&all_pos[2][1], free_nothing);
    node_t *cur_child = node_add_child(root, &all_pos[1][1]);
    cur_child = node_add_child(root, &all_pos[2][3]);
    cur_child = node_add_child(cur_child, &all_pos[4][3]);
    cur_child = node_add_child(cur_child, &all_pos[4][1]);
    cur_child = node_add_child(root, &all_pos[4][1]);
    cur_child = node_add_child(cur_child, &all_pos[4][3]);
    cur_child = node_add_child(cur_child, &all_pos[2][3]);

    return root;
}
node_t *get_expected_output_test_elephant()
{
    /*
    Order:
    seast
    south
    swest
    west
    no_dir
    east
    neast
    north
    nwest
    */
    node_t *root = tree_create(&all_pos[2][2], free_nothing);
    node_add_child(root, &all_pos[2][3]);
    node_add_child(root, &all_pos[1][3]);
    node_add_child(root, &all_pos[1][2]);
    node_add_child(root, &all_pos[0][2]);
    node_add_child(root, &all_pos[3][2]);
    node_add_child(root, &all_pos[4][2]);
    node_add_child(root, &all_pos[3][1]);
    node_add_child(root, &all_pos[2][0]);
    node_add_child(root, &all_pos[1][1]);


    return root;
}

void test_pawn(){
    struct world_t *world = world_init();
    position_t pos[] = {{2, 0}, {2, 2}, {3, 1}, {3, 3}, {4, 2}};
    for (int i = 0; i < 5; i++)
    {
        world_set_sort(world, position_to_idx(pos + i), PAWN);
    }
    position_t starting_position = {2, 1};
    world_set_sort(world, position_to_idx(&starting_position), PAWN);
    node_t *move_tree = get_moves(world, &starting_position);
    node_t *expected_output = get_expected_output_test_pawn();
    assert(are_trees_equal(expected_output, move_tree));
    node_free(move_tree);
    node_free(expected_output);
}

void vs_print_pos(void* vp){
    position_t *p = vp;
    printf("(%u,%u)", p->col, p->row);
}

void test_elephant(){
    struct world_t *world = world_init();
    
    position_t pos[] = {{2,1}, {3,3}};
    for (int i = 0; i < 2; i++)
    {
        world_set_sort(world, position_to_idx(pos + i), PAWN);
    }

    position_t starting_position = {2, 2};
    world_set_sort(world, position_to_idx(&starting_position), ELEPHANT);
    node_t *move_tree = get_moves(world, &starting_position);
    node_t *expected_output = get_expected_output_test_elephant();
    assert(are_trees_equal(expected_output, move_tree));
    node_free(move_tree);
    node_free(expected_output);
}

void test_moves()
{
    for(int i = 0; i<WIDTH; i++){
        for(int j = 0; j<HEIGHT; j++){
            all_pos[i][j].col = i;
            all_pos[i][j].row = j;
        }
    }
    test_pawn();
    
    test_elephant();
    
}