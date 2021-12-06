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
    for (int i = 0; i < 500; i++) {
        deleteFromAvlTreeTest(&map, i);
        assert(sizeOfAvlTreeTest(&map) == 999 - (size_t)i);
    }
    for (int i = 500; i < 1000; i++) {
        int val = getFromAvlTreeTest(&map, i);
        assert(val == 2*i);
    }
    deinitAvlTreeTest(&map);
    return 0;
}
