// test:

#include <assert.h>

#define TYPE unsigned long
#define TYPED(NAME) NAME ## Test

#include "rb-tree/rb-tree.c"

int main() {
    RBTreeTest map;
    initRBTreeTest(&map);
    for (TYPE i = 0; i < 1000; i++) {
        insertIntoRBTreeTest(&map, i*i*i*i);
        assert(sizeOfRBTreeTest(&map) == (size_t)i + 1);
    }
    for (TYPE i = 0; i < 500; i++) {
        deleteFromRBTreeTest(&map, i*i*i*i);
        assert(sizeOfRBTreeTest(&map) == 999 - (size_t)i);
    }
    for (TYPE i = 500; i < 1000; i++) {
        assert(hasInRBTreeTest(&map, i*i*i*i));
    }
    deinitRBTreeTest(&map);
    return 0;
}
