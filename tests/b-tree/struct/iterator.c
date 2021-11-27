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
    for (int i = 0; i < 1000; i++) {
        insertIntoBTreeTest(&map, TTT(2*999 - 2*i));
        assert(sizeOfBTreeTest(&map) == (size_t)i + 1);
        isBTree(&map);
    }
    BTreeIteratorTest it = getBTreeIteratorTest(&map);
    size_t i = 0;
    while (hasNextBTreeTest(&it)) {
        Test v = getNextBTreeTest(&it);
        assert(v.a >= 0 && v.a <= 2*999 && v.a % 2 == 0);
        isBTree(&map);
        i++;
    }
    assert(i == 1000);
    deinitBTreeTest(&map);
    return 0;
}

