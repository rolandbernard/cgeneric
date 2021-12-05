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
        assert(sizeOfBTreeTest(&map) == (size_t)i + 1);
    }
    BTreeIteratorTest it = getBTreeIteratorTest(&map);
    size_t i = 0;
    while (hasNextBTreeTest(&it)) {
        int v = getNextBTreeTest(&it);
        assert(getFromBTreeTest(&map, v) == 2*(int)v);
        i++;
    }
    assert(i == 1000);
    deinitBTreeTest(&map);
    return 0;
}

