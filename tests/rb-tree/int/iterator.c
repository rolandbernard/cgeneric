// test:

#include <assert.h>

#define LESS_THAN(A, B) (A < B)
#define TYPED(NAME) NAME ## Test

#include "rb-tree/rb-tree.c"
#include "../check-rb.c"

int main() {
    RBTreeTest map;
    initRBTreeTest(&map);
    for (int i = 0; i < 1000; i++) {
        insertIntoRBTreeTest(&map, 2*999 - 2*i);
        assert(sizeOfRBTreeTest(&map) == (size_t)i + 1);
        isRBTree(&map);
    }
    RBTreeIteratorTest it = getRBTreeIteratorTest(&map);
    int p = 0;
    size_t i = 0;
    while (hasNextRBTreeTest(&it)) {
        int v = getNextRBTreeTest(&it);
        assert(v >= 0 && v <= 2*999 && v % 2 == 0);
        assert(p <= v);
        p = v;
        isRBTree(&map);
        i++;
    }
    assert(i == 1000);
    deinitRBTreeTest(&map);
    return 0;
}

