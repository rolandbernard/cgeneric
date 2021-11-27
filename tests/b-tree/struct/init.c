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

int main() {
    BTreeTest map;
    initBTreeTest(&map);
    assert(sizeOfBTreeTest(&map) == 0);
    deinitBTreeTest(&map);
    return 0;
}
