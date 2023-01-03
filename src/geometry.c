#include "geometry.h"
#include <stdlib.h>
#include "util.h"

char place_buffer[3];
/**
 * The returned char* needs to be freed
 */
const char *place_to_string(enum color_t c, enum sort_t s)
{
    place_buffer[2] = 0;
    place_buffer[0] = color_to_char(c);
    place_buffer[1] = sort_to_char(s);
    return place_buffer;
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