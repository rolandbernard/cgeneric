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
    assert(sizeOfAvlTreeTest(&map) == 0);
    deinitAvlTreeTest(&map);
    return 0;
}
