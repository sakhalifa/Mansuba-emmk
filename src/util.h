#ifndef __UTIL_H__
#define __UTIL_H__

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>
#include "geometry.h"
typedef unsigned int uint;

typedef enum {
    SQUARE = 0,
    TRIANGULAR = 1,
    HEXAGONAL = 2
} relation_t;

typedef struct {
    enum color_t color;
    enum sort_t sort;
} piece_t;

typedef struct {
    uint index;
    piece_t piece;
} game_piece_t;


#endif