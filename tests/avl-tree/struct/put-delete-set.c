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
    for (int i = 0; i < 10000; i++) {
        if (rand() % 2 == 0) {
            insertIntoAvlTreeTest(&map, TTT(rand()));
        } else {
            deleteFromAvlTreeTest(&map, TTT(rand()));
        }
        if (i % 100 == 0) {
            isAvlTree(&map);
        }
    }
    isAvlTree(&map);
    deinitAvlTreeTest(&map);
    return 0;
}
