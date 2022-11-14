#include "main.h"


int main(){
    test_get_neighbors();
    test_get_neighbor();
    printf("Finished testing neighbors.c\n");

    test_array();
    printf("Finished testing array_list.c\n");

    test_linked();
    printf("Finished testing linked_list.c\n");

    // test_moves();
    // printf("Finished testing moves.c\n");

    return 0;
}