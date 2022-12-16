#include "util.h"


void _check_error( void * pointer, enum error_type error_type, uint line , const char * file){
    switch (error_type)
    {
    case MALLOC_ERR:
        if (pointer == NULL){
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

void free_nothing(void *_){
    _ = _; // remove warning
}

void flush_stdin(){
    int c;
    while( (c = fgetc( stdin )) != EOF && c != '\n' );
}

uint read_player_position(){
    uint column, row;
    int matches = scanf(" %u %u", &row, &column);
    flush_stdin();

    if (matches != 2){
        printf("Invalid input given !\n");
        return UINT_MAX;
    }

    if(column >= WIDTH || row >= HEIGHT){
        printf("The position given is not valid ! You asked for position row = %u, column = %u!\n", row, column);
        return UINT_MAX;
    }

    return row*WIDTH + column;
}