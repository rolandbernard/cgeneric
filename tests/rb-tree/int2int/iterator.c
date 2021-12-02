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
        assert(sizeOfRBTreeTest(&map) == (size_t)i + 1);
    }
    RBTreeIteratorTest it = getRBTreeIteratorTest(&map);
    size_t i = 0;
    while (hasNextRBTreeTest(&it)) {
        int v = getNextRBTreeTest(&it);
        assert(getFromRBTreeTest(&map, v) == 2*(int)v);
        i++;
    }
    assert(i == 1000);
    deinitRBTreeTest(&map);
    return 0;
}

