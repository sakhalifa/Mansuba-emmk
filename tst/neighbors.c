#include "neighbors.h"
#include "util.h"
#include "position.h"

uint count_neighs(struct neighbors_t n){
    uint cpt =0;
    for (int i = 0; i < MAX_NEIGHBORS && n.n[i].i != UINT_MAX; i++) cpt++;
    return cpt;
}

bool test_get_neighbors_square(void){
    
    init_neighbors(SQUARE);    
    assert(count_neighs(get_neighbors(0)) == 2);
    assert(count_neighs(get_neighbors(1)) == 3);
    assert(count_neighs(get_neighbors(4)) == 2);
    assert(count_neighs(get_neighbors(7)) == 4);
    assert(count_neighs(get_neighbors(18)) == 3);
    assert(count_neighs(get_neighbors(19)) == 2);
    assert(count_neighs(get_neighbors(20)) == 0);
    assert(count_neighs(get_neighbors(24)) == 0);
    assert(count_neighs(get_neighbors(-1)) == 0);
    assert(count_neighs(get_neighbors(100)) == 0);



    return true;
}

bool test_get_neighbors_triangle(void){
    init_neighbors(TRIANGULAR);

    assert(count_neighs(get_neighbors(0)) == 2);
    assert(count_neighs(get_neighbors(1)) == 2);
    assert(count_neighs(get_neighbors(2)) == 3);
    assert(count_neighs(get_neighbors(5)) == 2);
    assert(count_neighs(get_neighbors(6)) == 3);

    return true;
}

bool test_get_neighbor_square(void){
    init_neighbors(SQUARE);    

    uint n;
    n = get_neighbor(0, NORTH);
    assert(n == UINT_MAX);
    n = get_neighbor(0, SOUTH);
    assert(n == 5);
    n = get_neighbor(7, SEAST);
    assert(n == 13);
    n = get_neighbor(4, WEST);
    assert(n == 3);
    n = get_neighbor(4, EAST);
    assert(n == UINT_MAX);
    n = get_neighbor(9, SWEST);
    assert(n == 13);
    n = get_neighbor(19, NWEST);
    assert(n == 13);
    n = get_neighbor(19, NEAST);
    assert(n == UINT_MAX);
    n = get_neighbor(18, NEAST);
    assert(n == 14);

    n = get_neighbor(-4, NEAST);
    assert(n == UINT_MAX);  
    n = get_neighbor(20, NORTH);
    assert(n == UINT_MAX);
    n = get_neighbor(-5, SOUTH);
    assert(n == UINT_MAX);
    n = get_neighbor(24, SOUTH);
    assert(n == UINT_MAX);

    return true;
}

void test_get_neighbor_hexagonal(void){
    init_neighbors(HEXAGONAL);
    uint n;
    //cas normal gauche/droite
    n = get_neighbor(1, EAST);
    assert(n == 2);
    n = get_neighbor(1, WEST);
    assert(n == 0);
    //cas normal ligne paire
    n = get_neighbor(12, NEAST);
    assert(n == 7);
    n = get_neighbor(12, NWEST);
    assert(n == 6);
    n = get_neighbor(12, SEAST);
    assert(n == 17);
    n = get_neighbor(12, SWEST);
    assert(n == 16);

    //cas normal ligne impaire
    n = get_neighbor(7, NEAST);
    assert(n == 3);
    n = get_neighbor(7, NWEST);
    assert(n == 2);
    n = get_neighbor(7, SEAST);
    assert(n == 13);
    n = get_neighbor(7, SWEST);
    assert(n == 12);

    //cas limite ligne paire
    n = get_neighbor(0, WEST);
    assert(n == UINT_MAX);
    n = get_neighbor(0, SWEST);
    assert(n == UINT_MAX);
    n = get_neighbor(0, NWEST);
    assert(n == UINT_MAX);

    n = get_neighbor(4, EAST);
    assert(n == UINT_MAX);
    n = get_neighbor(4, NEAST);
    assert(n == UINT_MAX);
    n = get_neighbor(4, SEAST);
    assert(n == UINT_MAX);

    //cas limite ligne impaire
    n = get_neighbor(5, WEST);
    assert(n == UINT_MAX);
    n = get_neighbor(5, SWEST);
    assert(n == 10);
    n = get_neighbor(5, NWEST);
    assert(n == 0);

    n = get_neighbor(8, EAST);
    assert(n == UINT_MAX);
    n = get_neighbor(8, NEAST);
    assert(n == 4);
    n = get_neighbor(8, SEAST);
    assert(n == 14);
    
    
}
bool test_get_neighbor_triangle(void){
    
    init_neighbors(TRIANGULAR);

    assert(get_neighbor(0, NORTH) == UINT_MAX);
    assert(get_neighbor(0, SEAST) == UINT_MAX);
    assert(get_neighbor(1, EAST) == 2);
    assert(get_neighbor(1, SOUTH) == UINT_MAX);
    assert(get_neighbor(2, NORTH) == UINT_MAX);
    assert(get_neighbor(2, WEST) == 1);
    assert(get_neighbor(2, EAST) == 3);
    assert(get_neighbor(7, SOUTH) == UINT_MAX);
    assert(get_neighbor(7, NORTH) == 2);
    assert(get_neighbor(9, NORTH) == 4);
    assert(get_neighbor(9, EAST) == UINT_MAX);
    assert(get_neighbor(9, SOUTH) == UINT_MAX);
    assert(get_neighbor(19, SOUTH) == UINT_MAX);
    assert(get_neighbor(19, NORTH) == 14);
    assert(get_neighbor(19, EAST) == UINT_MAX);
    assert(get_neighbor(19, WEST) == 18);
    assert(get_neighbor(19, NWEST) == UINT_MAX);
    assert(get_neighbor(19, NEAST) == UINT_MAX);
    assert(get_neighbor(19, SEAST) == UINT_MAX);

    
    return true;
}

bool test_get_neighbors(void){
    return true;
}

bool test_get_neighbor(void){

    test_get_neighbor_square();
    test_get_neighbor_triangle();
    test_get_neighbor_hexagonal();

    return true;
}