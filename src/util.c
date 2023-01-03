#include "util.h"

void _check_error(void *pointer, enum error_type error_type, uint line, const char *file)
{
    switch (error_type)
    {
    case MALLOC_ERR:
        if (pointer == NULL)
        {
            fprintf(stderr, "Error at file %s:%u\nMalloc failed to allocate the needed memory.\n", file, line);
            exit(MALLOC_ERR);
        }
        break;
    case FILE_ERR:

        break;

    default:
        break;
    }
}

char color_to_char(enum color_t c)
{
    switch (c)
    {
    case WHITE:
        return 'W';
    case BLACK:
        return 'B';
    default:
        return '_';
    }
}

char sort_to_char(enum sort_t s)
{
    switch (s)
    {
    case PAWN:
        return 'P';
    case ELEPHANT:
        return 'E';
    case TOWER:
        return 'T';
    default:
        return '_';
    }
}

void free_nothing(void *_)
{
    _ = _; // remove warning
}