// test:

#include <limits.h>
#include <assert.h>

#define LESS_THAN(A, B) A < B
#define TYPED(NAME) NAME ## Test

#include "rb-tree/rb-tree.c"
#include "../check-rb.c"

int main() {
    RBTreeTest map;
    initRBTreeTest(&map);
    for (int i = 0; i < 1000; i++) {
        insertIntoRBTreeTest(&map, 1000 - i);
        assert(firstRBTreeTest(&map) == 1000 - i);
        assert(lastRBTreeTest(&map) == 1000);
    }
    for (int i = 0; i < 1000; i++) {
        insertIntoRBTreeTest(&map, 1000 + i);
        assert(firstRBTreeTest(&map) == 1);
        assert(lastRBTreeTest(&map) == 1000 + i);
    }
    isRBTree(&map);
    deinitRBTreeTest(&map);
    return 0;
}

