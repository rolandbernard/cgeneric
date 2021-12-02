// test:

#include <assert.h>

#define TYPED(NAME) NAME ## Test
#define IS_MAP

#include "rb-tree/rb-tree.c"

int main() {
    RBTreeTest map;
    initRBTreeTest(&map);
    assert(sizeOfRBTreeTest(&map) == 0);
    deinitRBTreeTest(&map);
    deinitRBTreeTest(&map);
    return 0;
}
