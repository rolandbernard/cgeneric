// test:

#include <assert.h>
#include <stdlib.h>

#define TYPED(NAME) NAME ## Test

#include "avl-tree/avl-tree.c"
#include "../check-avl.c"

int main() {
    AvlTreeTest map;
    initAvlTreeTest(&map);
    for (int i = 0; i < 10000; i++) {
        if (rand() % 2 == 0) {
            insertIntoAvlTreeTest(&map, rand() % 100);
        } else {
            deleteFromAvlTreeTest(&map, rand() % 100);
        }
        if (i % 100 == 0) {
            isAvlTree(&map);
        }
    }
    isAvlTree(&map);
    deinitAvlTreeTest(&map);
    return 0;
}
