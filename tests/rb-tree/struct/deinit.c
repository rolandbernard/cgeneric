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
    isRBTree(&map);
    assert(sizeOfRBTreeTest(&map) == 0);
    deinitRBTreeTest(&map);
    deinitRBTreeTest(&map);
    return 0;
}
