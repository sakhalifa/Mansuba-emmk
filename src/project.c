#include "project.h"

uint choose_random_piece_belonging_to(struct world_t *world, player_t *player)
{
    uint positions[WORLD_SIZE];
    uint index = 0;
    for (uint i = 0; i < WORLD_SIZE; i++)
    {
        if (world_get(world, i) == player->color)
        {
            positions[index] = i;
            index++;
        }
    }

    assert(index != 0);
    return positions[rand() % index];
}

node_t *choose_random_move_for_piece(struct world_t *world, uint piece)
{
    position_t position;
    position_from_idx(&position, piece);
    node_t *moves = get_moves(world, &position);

    uint len_children = moves->children->len;

    if (len_children == 0)
    {
        printf("no moves\n");
        node_free(moves);
        return NULL;
    }

    uint selected_child = rand() % (len_children);
    node_t *move_ending = array_list_get(moves->children, selected_child);
    len_children = move_ending->children->len;
    selected_child = rand() % (len_children + 1);

    while (selected_child != len_children)
    {
        len_children = move_ending->children->len;

        if (len_children == 0)
            break;
        move_ending = array_list_get(move_ending->children, selected_child);
        selected_child = rand() % (len_children + 1);
        assert(move_ending != NULL);
    }
    
    return move_ending;
}

void move_piece(struct world_t *world, node_t *move, player_t *player)
{

    world_set(world, position_to_idx((position_t *)move->value), player->color);
    world_set_sort(world, position_to_idx((position_t *)move->value), PAWN);
    while (move->parent != NULL)
    {
        move = move->parent;
    }

    world_set_sort(world, position_to_idx((position_t *)move->value), NO_SORT);
    world_set(world, position_to_idx((position_t *)move->value), NO_COLOR);

    node_free(move);

    return;
}

bool check_win(struct world_t *world)
{
    for (int i = 0; i < HEIGHT; i++)
    {
        if (world_get(world, (i * WIDTH)) == WHITE)
        {
            return true;
        }
        if (world_get(world, ((i + 1) * WIDTH) - 1) == BLACK)
        {
            return true;
        }
    }
    return false;
}

void world_populate(struct world_t *world)
{
    for (int i = 0; i < HEIGHT; i++)
    {
        world_set(world, (i * WIDTH), BLACK);
        world_set_sort(world, (i * WIDTH), PAWN);

        world_set(world, ((i + 1) * WIDTH) - 1, WHITE);
        world_set_sort(world, ((i + 1) * WIDTH) - 1, PAWN);
    }
}

void display_game(struct world_t *world)
{
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            printf(" %s", place_to_string(world_get(world, i * WIDTH + j), world_get_sort(world, i * WIDTH + j)));
        }
        printf("\n");
    }
    printf("\n");
}

int main()
{
    long seed = time(NULL);
    printf("%ld\n", seed);
    srand(seed);

    struct world_t *world = world_init();
    world_populate(world);
    init_players();
    player_t *player = get_random_player();
    uint turn_counter = 0;
    while (!check_win(world) && turn_counter < MAX_TURN)
    {
        // printf("Player: %d, turn : %d\n", player->color, turn_counter);
        // display_game(world);
        uint piece = choose_random_piece_belonging_to(world, player);

        node_t *move = choose_random_move_for_piece(world, piece);
        
        if (move != NULL)
        {
            move_piece(world, move, player);
        }
        player = next_player(player);
        turn_counter++;
    }

    printf("partie terminée après %u turns\n", turn_counter);
    display_game(world);
    return EXIT_SUCCESS;
}