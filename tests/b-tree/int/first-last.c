// test:

#include <limits.h>
#include <assert.h>

#define LESS_THAN(A, B) A < B
#define TYPED(NAME) NAME ## Test

#include "b-tree/b-tree.c"
#include "../check-b.c"

int main() {
    BTreeTest map;
    initBTreeTest(&map);
    for (int i = 0; i < 1000; i++) {
        insertIntoBTreeTest(&map, 1000 - i);
        assert(firstBTreeTest(&map) == 1000 - i);
        assert(lastBTreeTest(&map) == 1000);
    }
    for (int i = 0; i < 1000; i++) {
        insertIntoBTreeTest(&map, 1000 + i);
        assert(firstBTreeTest(&map) == 1);
        assert(lastBTreeTest(&map) == 1000 + i);
    }
    isBTree(&map);
    deinitBTreeTest(&map);
    return 0;
}

