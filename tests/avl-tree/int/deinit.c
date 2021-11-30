// test:

#include <assert.h>

#define TYPED(NAME) NAME ## Test

#include "avl-tree/avl-tree.c"
#include "../check-avl.c"

int main() {
    AvlTreeTest map;
    initAvlTreeTest(&map);
    isAvlTree(&map);
    assert(sizeOfAvlTreeTest(&map) == 0);
    deinitAvlTreeTest(&map);
    deinitAvlTreeTest(&map);
    return 0;
}
