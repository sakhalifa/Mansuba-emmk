#include "../src/neighbors.h"
#include "../src/util.h"

uint count_neighs(struct neighbors_t n){
    uint cpt =0;
    for (int i = 0; i < MAX_NEIGHBORS && n.n[i].i != UINT_MAX; i++) cpt++;
    return cpt;
}

bool test_get_neighbors(){
    
    assert(count_neighs(get_neighbors(0)) == 3);
    assert(count_neighs(get_neighbors(1)) == 5);
    assert(count_neighs(get_neighbors(4)) == 3);
    assert(count_neighs(get_neighbors(7)) == 8);
    assert(count_neighs(get_neighbors(18)) == 5);
    assert(count_neighs(get_neighbors(19)) == 3);
    assert(count_neighs(get_neighbors(20)) == 0);
    assert(count_neighs(get_neighbors(24)) == 0);
    assert(count_neighs(get_neighbors(-1)) == 0);
    assert(count_neighs(get_neighbors(100)) == 0);

    return true;
}

bool test_get_neighbor(){



    return true;
}