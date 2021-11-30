// test:

#include <assert.h>

#define LESS_THAN(A, B) (A < B)
#define TYPED(NAME) NAME ## Test

#include "avl-tree/avl-tree.c"
#include "../check-avl.c"

int main() {
    AvlTreeTest map;
    initAvlTreeTest(&map);
    for (int i = 0; i < 1000; i++) {
        insertIntoAvlTreeTest(&map, 2*999 - 2*i);
        assert(sizeOfAvlTreeTest(&map) == (size_t)i + 1);
        isAvlTree(&map);
    }
    AvlTreeIteratorTest it = getAvlTreeIteratorTest(&map);
    int p = 0;
    size_t i = 0;
    while (hasNextAvlTreeTest(&it)) {
        int v = getNextAvlTreeTest(&it);
        assert(v >= 0 && v <= 2*999 && v % 2 == 0);
        assert(p <= v);
        p = v;
        isAvlTree(&map);
        i++;
    }
    assert(i == 1000);
    deinitAvlTreeTest(&map);
    return 0;
}

