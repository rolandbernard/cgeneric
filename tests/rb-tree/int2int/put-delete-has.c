// test:

#include <assert.h>

#define TYPED(NAME) NAME ## Test
#define IS_MAP

#include "rb-tree/rb-tree.c"

int main() {
    RBTreeTest map;
    initRBTreeTest(&map);
    for (int i = 0; i < 1000; i++) {
        putInRBTreeTest(&map, i, 2*i);
        assert(sizeOfRBTreeTest(&map) == 1 + (size_t)i);
    }
    for (int i = 0; i < 500; i++) {
        deleteFromRBTreeTest(&map, i);
        assert(sizeOfRBTreeTest(&map) == 999 - (size_t)i);
    }
    for (int i = 0; i < 500; i++) {
        assert(!hasInRBTreeTest(&map, i));
    }
    for (int i = 500; i < 1000; i++) {
        assert(hasInRBTreeTest(&map, i));
    }
    deinitRBTreeTest(&map);
    return 0;
}
