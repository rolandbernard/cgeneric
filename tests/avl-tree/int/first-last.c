// test:

#include <limits.h>
#include <assert.h>

#define LESS_THAN(A, B) A < B
#define TYPED(NAME) NAME ## Test

#include "avl-tree/avl-tree.c"
#include "../check-avl.c"

int main() {
    AvlTreeTest map;
    initAvlTreeTest(&map);
    for (int i = 0; i < 1000; i++) {
        insertIntoAvlTreeTest(&map, 1000 - i);
        assert(firstAvlTreeTest(&map) == 1000 - i);
        assert(lastAvlTreeTest(&map) == 1000);
    }
    for (int i = 0; i < 1000; i++) {
        insertIntoAvlTreeTest(&map, 1000 + i);
        assert(firstAvlTreeTest(&map) == 1);
        assert(lastAvlTreeTest(&map) == 1000 + i);
    }
    isAvlTree(&map);
    deinitAvlTreeTest(&map);
    return 0;
}

