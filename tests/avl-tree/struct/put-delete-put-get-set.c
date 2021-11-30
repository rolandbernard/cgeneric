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
#define IS_SET

#include "avl-tree/avl-tree.c"
#include "../check-avl.c"

int main() {
    AvlTreeTest map;
    initAvlTreeTest(&map);
    for (int i = 0; i < 1000; i++) {
        insertIntoAvlTreeTest(&map, TTT(i*i));
        assert(sizeOfAvlTreeTest(&map) == 1 + (size_t)i);
        isAvlTree(&map);
    }
    for (int i = 0; i < 1000; i++) {
        insertIntoAvlTreeTest(&map, TTT(i*i));
        assert(sizeOfAvlTreeTest(&map) == 1000);
        isAvlTree(&map);
    }
    for (int i = 0; i < 500; i++) {
        deleteFromAvlTreeTest(&map, TTT(i*i));
        assert(sizeOfAvlTreeTest(&map) == 999 - (size_t)i);
        isAvlTree(&map);
    }
    for (int i = 0; i < 500; i++) {
        deleteFromAvlTreeTest(&map, TTT(i*i));
        assert(sizeOfAvlTreeTest(&map) == 500);
        isAvlTree(&map);
    }
    for (int i = 0; i < 500; i++) {
        insertIntoAvlTreeTest(&map, TTT(i*i));
        assert(sizeOfAvlTreeTest(&map) == 501 + (size_t)i);
        isAvlTree(&map);
    }
    for (int i = 0; i < 500; i++) {
        insertIntoAvlTreeTest(&map, TTT(i*i));
        assert(sizeOfAvlTreeTest(&map) == 1000);
        isAvlTree(&map);
    }
    for (int i = 0; i < 1000; i++) {
        assert(hasInAvlTreeTest(&map, TTT(i*i)));
        isAvlTree(&map);
    }
    deinitAvlTreeTest(&map);
    return 0;
}
