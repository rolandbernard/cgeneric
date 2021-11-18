// test:

#include <assert.h>

#define TYPED(NAME) NAME ## Test

#include "rb-tree/rb-tree.c"

int main() {
    RBTreeTest map;
    initRBTreeTest(&map);
    for (int i = 0; i < 1000; i++) {
        insertIntoRBTreeTest(&map, i*i);
        assert(sizeOfRBTreeTest(&map) == (size_t)i + 1);
    }
    for (int i = 0; i < 1000; i++) {
        assert(hasInRBTreeTest(&map, i*i));
    }
    deinitRBTreeTest(&map);
    return 0;
}
