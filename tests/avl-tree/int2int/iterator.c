// test:

#include <assert.h>

#define TYPED(NAME) NAME ## Test
#define IS_MAP

#include "avl-tree/avl-tree.c"

int main() {
    AvlTreeTest map;
    initAvlTreeTest(&map);
    for (int i = 0; i < 1000; i++) {
        putInAvlTreeTest(&map, i, 2*i);
        assert(sizeOfAvlTreeTest(&map) == (size_t)i + 1);
    }
    AvlTreeIteratorTest it = getAvlTreeIteratorTest(&map);
    size_t i = 0;
    while (hasNextAvlTreeTest(&it)) {
        int v = getNextAvlTreeTest(&it);
        assert(getFromAvlTreeTest(&map, v) == 2*(int)v);
        i++;
    }
    assert(i == 1000);
    deinitAvlTreeTest(&map);
    return 0;
}

