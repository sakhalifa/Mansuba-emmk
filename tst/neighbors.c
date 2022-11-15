#include "../src/neighbors.h"
#include "../src/util.h"

uint count_neighs(struct neighbors_t n){
    uint cpt =0;
    for (int i = 0; i < MAX_NEIGHBORS && n.n[i].i != UINT_MAX; i++) cpt++;
    return cpt;
}

//TODO: remake tests
bool test_get_neighbors(){
    
    // assert(count_neighs(get_neighbors(0)) == 3);
    // assert(count_neighs(get_neighbors(1)) == 5);
    // assert(count_neighs(get_neighbors(4)) == 3);
    // assert(count_neighs(get_neighbors(7)) == 8);
    // assert(count_neighs(get_neighbors(18)) == 5);
    // assert(count_neighs(get_neighbors(19)) == 3);
    // assert(count_neighs(get_neighbors(20)) == 0);
    // assert(count_neighs(get_neighbors(24)) == 0);
    // assert(count_neighs(get_neighbors(-1)) == 0);
    // assert(count_neighs(get_neighbors(100)) == 0);



    return true;
}

bool test_get_neighbor(){

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