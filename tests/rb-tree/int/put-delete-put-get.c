// test:

#include <assert.h>

#define TYPED(NAME) NAME ## Test

#include "rb-tree/rb-tree.c"

int main() {
    RBTreeTest map;
    initRBTreeTest(&map);
    for (int i = 0; i < 1000; i++) {
        insertIntoRBTreeTest(&map, i*i);
        assert(sizeOfRBTreeTest(&map) == 1 + (size_t)i);
    }
    for (int i = 0; i < 500; i++) {
        deleteFromRBTreeTest(&map, i*i);
        assert(sizeOfRBTreeTest(&map) == 999 - (size_t)i);
    }
    for (int i = 0; i < 500; i++) {
        insertIntoRBTreeTest(&map, i*i);
        assert(sizeOfRBTreeTest(&map) == 501 + (size_t)i);
    }
    for (int i = 0; i < 1000; i++) {
        assert(hasInRBTreeTest(&map, i*i));
    }
    deinitRBTreeTest(&map);
    return 0;
}
