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

#include "avl-tree/avl-tree.c"

int main() {
    AvlTreeTest map;
    initAvlTreeTest(&map);
    assert(sizeOfAvlTreeTest(&map) == 0);
    deinitAvlTreeTest(&map);
    return 0;
}
