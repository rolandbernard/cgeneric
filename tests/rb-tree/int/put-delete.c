// test:

#include <assert.h>

#define TYPED(NAME) NAME ## Test

#include "rb-tree/rb-tree.c"
#include "../check-rb.c"

int main() {
    RBTreeTest map;
    initRBTreeTest(&map);
    for (int i = 0; i < 10000; i++) {
        if (rand() % 2 == 0) {
            insertIntoRBTreeTest(&map, rand() % 100);
        } else {
            deleteFromRBTreeTest(&map, rand() % 100);
        }
        if (i % 100 == 0) {
            isRBTree(&map);
        }
    }
    isRBTree(&map);
    deinitRBTreeTest(&map);
    return 0;
}
