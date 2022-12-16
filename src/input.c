#include "util.h"

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