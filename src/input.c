#include "input.h"
#include "util.h"

void flush_stdin(void){
    int c;
    while( (c = fgetc( stdin )) != EOF && c != '\n' );
}

uint read_user_position(void){
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


enum actions read_user_action(void){
    char action;
    int matches = scanf("%c", &action);
    flush_stdin();

    if (matches != 1) {
        printf("Invalid action given !\n");
        return MAX_ACTION;
    }

    if (action == 'm') return MOVE; 
    if (action == 'w') return WAIT; 
    if (action == 'e') return ESCAPE;
    return MAX_ACTION; 
}

uint read_user_number(void){
    uint number;
    int matches = scanf("%d", &number);
    flush_stdin();

    if (matches != 1) {
        printf("Invalid action given !\n");
        return MAX_ACTION;
    }

    return number;
}
