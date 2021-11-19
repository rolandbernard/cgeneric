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

#include "rb-tree/rb-tree.c"
#include "../check-rb.c"

int main() {
    RBTreeTest map;
    initRBTreeTest(&map);
    for (int i = 0; i < 10000; i++) {
        if (rand() % 2 == 0) {
            insertIntoRBTreeTest(&map, TTT(rand()));
        } else {
            deleteFromRBTreeTest(&map, TTT(rand()));
        }
        if (i % 100 == 0) {
            isRBTree(&map);
        }
    }
    isRBTree(&map);
    deinitRBTreeTest(&map);
    return 0;
}
