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
    assert(sizeOfRBTreeTest(&map) == 0);
    deinitRBTreeTest(&map);
    deinitRBTreeTest(&map);
    return 0;
}
