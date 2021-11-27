// test:

#include <assert.h>

#define TYPE unsigned long
#define TYPED(NAME) NAME ## Test

#include "b-tree/b-tree.c"
#include "../check-b.c"

int main() {
    BTreeTest map;
    initBTreeTest(&map);
    for (TYPE i = 0; i < 1000; i++) {
        insertIntoBTreeTest(&map, i*i*i*i);
        assert(sizeOfBTreeTest(&map) == (size_t)i + 1);
        isBTree(&map);
    }
    for (TYPE i = 0; i < 500; i++) {
        deleteFromBTreeTest(&map, i*i*i*i);
        assert(sizeOfBTreeTest(&map) == 999 - (size_t)i);
        isBTree(&map);
    }
    for (TYPE i = 500; i < 1000; i++) {
        assert(hasInBTreeTest(&map, i*i*i*i));
        isBTree(&map);
    }
    deinitBTreeTest(&map);
    return 0;
}
