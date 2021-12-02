// test:

#include <assert.h>
#include <string.h>

#define TYPED(NAME) NAME ## Test

#define TYPE const char*
#define LESS_THAN(FIRST, SECOND) (strcmp(FIRST, SECOND) < 0)
#define IS_MAP

#include "rb-tree/rb-tree.c"

int main() {
    RBTreeTest map;
    initRBTreeTest(&map);
    putInRBTreeTest(&map, "Hello", 1);
    assert(sizeOfRBTreeTest(&map) == 1);
    putInRBTreeTest(&map, "World", 2);
    assert(sizeOfRBTreeTest(&map) == 2);
    putInRBTreeTest(&map, "Ok", 4);
    assert(sizeOfRBTreeTest(&map) == 3);
    putInRBTreeTest(&map, "Test", 4);
    assert(sizeOfRBTreeTest(&map) == 4);
    assert(getFromRBTreeTest(&map, "Hello") == 1);
    assert(getFromRBTreeTest(&map, "World") == 2);
    assert(getFromRBTreeTest(&map, "Ok") == 4);
    assert(getFromRBTreeTest(&map, "Test") == 4);
    deinitRBTreeTest(&map);
    return 0;
}
