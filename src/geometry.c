#include "geometry.h"
#include <stdlib.h>

/**
 * The returned char* needs to be freed
 */
const char *place_to_string(enum color_t c, enum sort_t s)
{
    switch (c)
    {
    case BLACK:
        switch (s)
        {
        case PAWN:
            return "BP";
        default:
            return "B_";
        }
    case WHITE:
        switch (s)
        {
        case PAWN:
            return "WP";
        default:
            return "W_";
        }
    default:
        switch (s)
        {
        case PAWN:
            return "_P";
        default:
            return "__";
        }
    }
}

const char *dir_to_string(enum dir_t d)
{
    switch (d)
    {
    case EAST:
        return "E";
    case SOUTH:
        return "S";
    case NORTH:
        return "N";
    case WEST:
        return "W";
    case NEAST:
        return "NE";
    case SEAST:
        return "SE";
    case NWEST:
        return "NW";
    case SWEST:
        return "SW";
    default:
        return "_";
    }
}