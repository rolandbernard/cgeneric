// test:

#include <assert.h>

#define TYPED(NAME) NAME ## Test

#include "rb-tree/rb-tree.c"
#include "../check-rb.c"

int main() {
    RBTreeTest map;
    initRBTreeTest(&map);
    for (int i = 0; i < 1000; i++) {
        insertIntoRBTreeTest(&map, i);
        assert(sizeOfRBTreeTest(&map) == 1 + (size_t)i);
        isRBTree(&map);
    }
    for (int i = 0; i < 500; i++) {
        deleteFromRBTreeTest(&map, i);
        assert(sizeOfRBTreeTest(&map) == 999 - (size_t)i);
        isRBTree(&map);
    }
    for (int i = 0; i < 500; i++) {
        assert(!hasInRBTreeTest(&map, i));
        isRBTree(&map);
    }
    for (int i = 500; i < 1000; i++) {
        assert(hasInRBTreeTest(&map, i));
        isRBTree(&map);
    }
    deinitRBTreeTest(&map);
    return 0;
}
