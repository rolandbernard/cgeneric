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
    for (int i = 0; i < 1000; i++) {
        int val = getFromRBTreeTest(&map, i);
        assert(val == 2*i);
    }
    deinitRBTreeTest(&map);
    return 0;
}
