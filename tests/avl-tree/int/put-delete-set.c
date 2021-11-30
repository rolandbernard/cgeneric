// test:

#include <assert.h>

#define TYPED(NAME) NAME ## Test
#define IS_SET

#include "avl-tree/avl-tree.c"
#include "../check-avl.c"

int main() {
    AvlTreeTest map;
    initAvlTreeTest(&map);
    for (int i = 0; i < 10000; i++) {
        if (rand() % 2 == 0) {
            insertIntoAvlTreeTest(&map, rand());
        } else {
            deleteFromAvlTreeTest(&map, rand());
        }
        if (i % 100 == 0) {
            isAvlTree(&map);
        }
    }
    isAvlTree(&map);
    deinitAvlTreeTest(&map);
    return 0;
}
