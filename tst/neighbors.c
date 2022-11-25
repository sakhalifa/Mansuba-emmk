#include "neighbors.h"
#include "util.h"

uint count_neighs(struct neighbors_t n){
    uint cpt =0;
    for (int i = 0; i < MAX_NEIGHBORS && n.n[i].i != UINT_MAX; i++) cpt++;
    return cpt;
}

bool test_get_neighbors_square(){
    
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

bool test_get_neighbors_triangle(){
    init_neighbors(TRIANGULAR);

    assert(count_neighs(get_neighbors(0)) == 2);
    assert(count_neighs(get_neighbors(1)) == 2);
    assert(count_neighs(get_neighbors(2)) == 3);
    assert(count_neighs(get_neighbors(5)) == 2);
    assert(count_neighs(get_neighbors(6)) == 3);

    return true;
}

bool test_get_neighbor(){
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
}

void test_get_neighbor_hexagonal(){
    init_neighbors(2);
}

bool test_get_neighbor(){

    test_get_neighbor_square();
    test_get_neighbor_hexagonal();

    return true;
}