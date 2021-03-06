// test:

#include <assert.h>

#define TYPED(NAME) NAME ## Test

#include "rb-tree/rb-tree.c"
#include "../check-rb.c"

int main() {
    RBTreeTest map;
    initRBTreeTest(&map);
    isRBTree(&map);
    assert(sizeOfRBTreeTest(&map) == 0);
    deinitRBTreeTest(&map);
    deinitRBTreeTest(&map);
    return 0;
}
