// test:

#include <assert.h>

#define TYPED(NAME) NAME ## Test

#include "rb-tree/rb-tree.c"
#include "../check-rb.c"

int main() {
    RBTreeTest map;
    initRBTreeTest(&map);
    for (int i = 0; i < 1000; i++) {
        insertIntoRBTreeTest(&map, i*i);
        assert(sizeOfRBTreeTest(&map) == (size_t)i + 1);
        isRBTree(&map);
    }
    for (int i = 0; i < 1000; i++) {
        assert(hasInRBTreeTest(&map, i*i));
        isRBTree(&map);
    }
    deinitRBTreeTest(&map);
    return 0;
}
