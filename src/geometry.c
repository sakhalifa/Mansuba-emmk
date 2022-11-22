#include "geometry.h"
#include <stdlib.h>

char place_buffer[3];
/**
 * The returned char* needs to be freed
 */
const char *place_to_string(enum color_t c, enum sort_t s)
{
    place_buffer[2] = 0;
    switch(c){
        case BLACK:
            place_buffer[0] = 'B';
            break;
        case WHITE:
            place_buffer[0] = 'W';
            break;
        default:
            place_buffer[0] = '_';
    }
    switch(s){
        case PAWN:
            place_buffer[1] = 'P';
            break;
        // case TOWER:
        //     place_buffer[1] = 'T';
        //     break;
        // case ELEPHANT:
        //     place_buffer[1] = 'E';
        //     break;
        default:
            place_buffer[1] = '_';
            break;
    }
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