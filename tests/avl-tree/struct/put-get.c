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
#include "../check-avl.c"

int main() {
    AvlTreeTest map;
    initAvlTreeTest(&map);
    for (int i = 0; i < 1000; i++) {
        insertIntoAvlTreeTest(&map, TTT(i*i));
        assert(sizeOfAvlTreeTest(&map) == (size_t)i + 1);
        isAvlTree(&map);
    }
    for (int i = 0; i < 1000; i++) {
        assert(hasInAvlTreeTest(&map, TTT(i*i)));
        isAvlTree(&map);
    }
    deinitAvlTreeTest(&map);
    return 0;
}
