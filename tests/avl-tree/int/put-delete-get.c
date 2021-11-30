// test:

#include <assert.h>

#define TYPE unsigned long
#define TYPED(NAME) NAME ## Test

#include "avl-tree/avl-tree.c"
#include "../check-avl.c"

int main() {
    AvlTreeTest map;
    initAvlTreeTest(&map);
    for (TYPE i = 0; i < 1000; i++) {
        insertIntoAvlTreeTest(&map, i*i*i*i);
        assert(sizeOfAvlTreeTest(&map) == (size_t)i + 1);
        isAvlTree(&map);
    }
    for (TYPE i = 0; i < 500; i++) {
        deleteFromAvlTreeTest(&map, i*i*i*i);
        assert(sizeOfAvlTreeTest(&map) == 999 - (size_t)i);
        isAvlTree(&map);
    }
    for (TYPE i = 500; i < 1000; i++) {
        assert(hasInAvlTreeTest(&map, i*i*i*i));
        isAvlTree(&map);
    }
    deinitAvlTreeTest(&map);
    return 0;
}
