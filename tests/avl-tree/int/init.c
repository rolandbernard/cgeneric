// test:

#include <assert.h>

#define TYPED(NAME) NAME ## Test

#include "avl-tree/avl-tree.c"

int main() {
    AvlTreeTest map;
    initAvlTreeTest(&map);
    assert(sizeOfAvlTreeTest(&map) == 0);
    deinitAvlTreeTest(&map);
    return 0;
}
