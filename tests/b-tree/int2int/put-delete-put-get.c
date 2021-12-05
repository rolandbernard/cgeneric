// test:

#include <assert.h>

#define TYPED(NAME) NAME ## Test
#define IS_MAP

#include "b-tree/b-tree.c"

int main() {
    BTreeTest map;
    initBTreeTest(&map);
    for (int i = 0; i < 1000; i++) {
        putInBTreeTest(&map, i, 2*i);
        assert(sizeOfBTreeTest(&map) == 1 + (size_t)i);
    }
    for (int i = 0; i < 500; i++) {
        deleteFromBTreeTest(&map, i);
        assert(sizeOfBTreeTest(&map) == 999 - (size_t)i);
    }
    for (int i = 0; i < 500; i++) {
        putInBTreeTest(&map, i, 2*i);
        assert(sizeOfBTreeTest(&map) == 501 + (size_t)i);
    }
    for (int i = 0; i < 1000; i++) {
        int val = getFromBTreeTest(&map, i);
        assert(val == 2*i);
    }
    deinitBTreeTest(&map);
    return 0;
}
