#include "world.h"
#include <stdlib.h>
#include <stdbool.h>

struct world_t {
    enum sort_t sort_array[WORLD_SIZE];
    enum color_t color_array[WORLD_SIZE];
};