// test:

#include <assert.h>
#include <string.h>

#define TYPED(NAME) NAME ## Test

#define TYPE const char*
#define LESS_THAN(FIRST, SECOND) (strcmp(FIRST, SECOND) < 0)
#define IS_MAP

#include "avl-tree/avl-tree.c"

int main() {
    AvlTreeTest map;
    initAvlTreeTest(&map);
    putInAvlTreeTest(&map, "Hello", 1);
    assert(sizeOfAvlTreeTest(&map) == 1);
    putInAvlTreeTest(&map, "World", 2);
    assert(sizeOfAvlTreeTest(&map) == 2);
    putInAvlTreeTest(&map, "Ok", 4);
    assert(sizeOfAvlTreeTest(&map) == 3);
    putInAvlTreeTest(&map, "Test", 4);
    assert(sizeOfAvlTreeTest(&map) == 4);
    deleteFromAvlTreeTest(&map, "Ok");
    assert(sizeOfAvlTreeTest(&map) == 3);
    deleteFromAvlTreeTest(&map, "Test");
    assert(sizeOfAvlTreeTest(&map) == 2);
    putInAvlTreeTest(&map, "Ok", 4);
    assert(sizeOfAvlTreeTest(&map) == 3);
    putInAvlTreeTest(&map, "Test", 4);
    assert(sizeOfAvlTreeTest(&map) == 4);
    assert(getFromAvlTreeTest(&map, "Hello") == 1);
    assert(getFromAvlTreeTest(&map, "World") == 2);
    assert(getFromAvlTreeTest(&map, "Ok") == 4);
    assert(getFromAvlTreeTest(&map, "Test") == 4);
    deinitAvlTreeTest(&map);
    return 0;
}
