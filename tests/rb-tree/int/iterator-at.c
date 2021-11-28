// test:

#include <assert.h>
#include <stdio.h>

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
    for (int i = 0; i < 1000; i++) {
        insertIntoRBTreeTest(&map, 2*999 - 2*i);
        assert(sizeOfRBTreeTest(&map) == (size_t)i + 1001);
        isRBTree(&map);
    }
    RBTreeIteratorTest it = getRBTreeIteratorAtTest(&map, 997);
    int p = 0;
    size_t i = 0;
    while (hasNextRBTreeTest(&it)) {
        int v = getNextRBTreeTest(&it);
        assert(v >= 998 && v <= 2*999 && v % 2 == 0);
        assert(p <= v);
        p = v;
        isRBTree(&map);
        i++;
    }
    assert(i == 1002);
    deinitRBTreeTest(&map);
    return 0;
}

