// test:

#include <assert.h>

#include "segment-tree/tree.c"

#define N 1000
    
int main() {
    int* tree = createSegmentTreeInt(N);
    int sum = 0;
    for (size_t i = 0; i < N; i++) {
        setInSegmentTreeInt(tree, N, i, 2*i);
        if (i >= 100) {
            assert(querySegmentTreeInt(tree, N, i - 100, i) == sum);
            sum -= 2*(i - 100);
        }
        sum += 2*i;
    }
    FREE(tree);
    return 0;
}

