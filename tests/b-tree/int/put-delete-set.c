// test:

#include <assert.h>

#define TYPED(NAME) NAME ## Test
#define IS_SET

#include "b-tree/b-tree.c"
#include "../check-b.c"

int main() {
    BTreeTest map;
    initBTreeTest(&map);
    for (int i = 0; i < 10000; i++) {
        if (rand() % 2 == 0) {
            insertIntoBTreeTest(&map, rand());
        } else {
            deleteFromBTreeTest(&map, rand());
        }
        if (i % 100 == 0) {
            isBTree(&map);
        }
    }
    isBTree(&map);
    deinitBTreeTest(&map);
    return 0;
}
