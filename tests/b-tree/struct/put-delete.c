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
    for (int i = 0; i < 10000; i++) {
        if (rand() % 2 == 0) {
            insertIntoBTreeTest(&map, TTT(rand() % 100));
        } else {
            deleteFromBTreeTest(&map, TTT(rand() % 100));
        }
        if (i % 100 == 0) {
            isBTree(&map);
        }
    }
    isBTree(&map);
    deinitBTreeTest(&map);
    return 0;
}
