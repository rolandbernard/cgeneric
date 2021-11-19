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

#include "rb-tree/rb-tree.c"
#include "../check-rb.c"

int main() {
    RBTreeTest map;
    initRBTreeTest(&map);
    for (int i = 0; i < 1000; i++) {
        insertIntoRBTreeTest(&map, TTT(i));
        assert(sizeOfRBTreeTest(&map) == 1 + (size_t)i);
        isRBTree(&map);
    }
    for (int i = 0; i < 500; i++) {
        deleteFromRBTreeTest(&map, TTT(i));
        assert(sizeOfRBTreeTest(&map) == 999 - (size_t)i);
        isRBTree(&map);
    }
    for (int i = 0; i < 500; i++) {
        assert(!hasInRBTreeTest(&map, TTT(i)));
        isRBTree(&map);
    }
    for (int i = 500; i < 1000; i++) {
        assert(hasInRBTreeTest(&map, TTT(i)));
        isRBTree(&map);
    }
    deinitRBTreeTest(&map);
    return 0;
}
