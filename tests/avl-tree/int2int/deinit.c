// test:

#include <assert.h>

#define TYPED(NAME) NAME ## Test
#define IS_MAP

#include "avl-tree/avl-tree.c"

int main() {
    AvlTreeTest map;
    initAvlTreeTest(&map);
    assert(sizeOfAvlTreeTest(&map) == 0);
    deinitAvlTreeTest(&map);
    deinitAvlTreeTest(&map);
    return 0;
}
