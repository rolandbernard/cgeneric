// test:

#include <assert.h>
#include <string.h>

#define TYPED(NAME) NAME ## Test

#define TYPE const char*
#define LESS_THAN(FIRST, SECOND) (strcmp(FIRST, SECOND) < 0)
#define IS_MAP

#include "b-tree/b-tree.c"

int main() {
    BTreeTest map;
    initBTreeTest(&map);
    putInBTreeTest(&map, "Hello", 1);
    assert(sizeOfBTreeTest(&map) == 1);
    putInBTreeTest(&map, "World", 2);
    assert(sizeOfBTreeTest(&map) == 2);
    putInBTreeTest(&map, "Ok", 4);
    assert(sizeOfBTreeTest(&map) == 3);
    putInBTreeTest(&map, "Test", 4);
    assert(sizeOfBTreeTest(&map) == 4);
    deleteFromBTreeTest(&map, "Ok");
    assert(sizeOfBTreeTest(&map) == 3);
    deleteFromBTreeTest(&map, "Test");
    assert(sizeOfBTreeTest(&map) == 2);
    putInBTreeTest(&map, "Ok", 4);
    assert(sizeOfBTreeTest(&map) == 3);
    putInBTreeTest(&map, "Test", 4);
    assert(sizeOfBTreeTest(&map) == 4);
    assert(getFromBTreeTest(&map, "Hello") == 1);
    assert(getFromBTreeTest(&map, "World") == 2);
    assert(getFromBTreeTest(&map, "Ok") == 4);
    assert(getFromBTreeTest(&map, "Test") == 4);
    deinitBTreeTest(&map);
    return 0;
}
