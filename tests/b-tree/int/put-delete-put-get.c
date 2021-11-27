// test:

#include <assert.h>

#define TYPED(NAME) NAME ## Test

#include "b-tree/b-tree.c"
#include "../check-b.c"

int main() {
    BTreeTest map;
    initBTreeTest(&map);
    for (int i = 0; i < 1000; i++) {
        insertIntoBTreeTest(&map, i*i);
        assert(sizeOfBTreeTest(&map) == 1 + (size_t)i);
        isBTree(&map);
    }
    for (int i = 0; i < 500; i++) {
        deleteFromBTreeTest(&map, i*i);
        assert(sizeOfBTreeTest(&map) == 999 - (size_t)i);
        isBTree(&map);
    }
    for (int i = 0; i < 500; i++) {
        insertIntoBTreeTest(&map, i*i);
        assert(sizeOfBTreeTest(&map) == 501 + (size_t)i);
        isBTree(&map);
    }
    for (int i = 0; i < 1000; i++) {
        assert(hasInBTreeTest(&map, i*i));
        isBTree(&map);
    }
    deinitBTreeTest(&map);
    return 0;
}
