// test:

#include <assert.h>

#define TYPED(NAME) NAME ## Test

#include "b-tree/b-tree.c"

int main() {
    BTreeTest map;
    initBTreeTest(&map);
    assert(sizeOfBTreeTest(&map) == 0);
    deinitBTreeTest(&map);
    return 0;
}
