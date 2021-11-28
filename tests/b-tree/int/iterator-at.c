// test:

#include <assert.h>
#include <stdio.h>

#define LESS_THAN(A, B) (A < B)
#define TYPED(NAME) NAME ## Test

#include "b-tree/b-tree.c"
#include "../check-b.c"

int main() {
    BTreeTest map;
    initBTreeTest(&map);
    for (int i = 0; i < 1000; i++) {
        insertIntoBTreeTest(&map, 2*999 - 2*i);
        assert(sizeOfBTreeTest(&map) == (size_t)i + 1);
        isBTree(&map);
    }
    for (int i = 0; i < 1000; i++) {
        insertIntoBTreeTest(&map, 2*999 - 2*i);
        assert(sizeOfBTreeTest(&map) == (size_t)i + 1001);
        isBTree(&map);
    }
    BTreeIteratorTest it = getBTreeIteratorAtTest(&map, 997);
    int p = 0;
    size_t i = 0;
    while (hasNextBTreeTest(&it)) {
        int v = getNextBTreeTest(&it);
        assert(v >= 998 && v <= 2*999 && v % 2 == 0);
        assert(p <= v);
        p = v;
        isBTree(&map);
        i++;
    }
    assert(i == 1002);
    deinitBTreeTest(&map);
    return 0;
}

