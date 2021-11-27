// test:

#include <assert.h>

typedef struct {
    int a;
    float b;
    double c;
} Test;

Test buildTest(int a, float b, double c) {
    Test ret = {a, b, c};
    return ret;
}

#define TTT(N) buildTest(N, N/(float)2, N/(double)4)

#define TYPE Test
#define TYPED(NAME) NAME ## Test

#include "b-tree/b-tree.c"
#include "../check-b.c"

int main() {
    BTreeTest map;
    initBTreeTest(&map);
    for (size_t i = 0; i < 1000; i++) {
        insertIntoBTreeTest(&map, TTT(i*i*i*i));
        assert(sizeOfBTreeTest(&map) == i + 1);
        isBTree(&map);
    }
    for (size_t i = 0; i < 500; i++) {
        deleteFromBTreeTest(&map, TTT(i*i*i*i));
        assert(sizeOfBTreeTest(&map) == 999 - i);
        isBTree(&map);
    }
    for (size_t i = 500; i < 1000; i++) {
        assert(hasInBTreeTest(&map, TTT(i*i*i*i)));
        isBTree(&map);
    }
    deinitBTreeTest(&map);
    return 0;
}
