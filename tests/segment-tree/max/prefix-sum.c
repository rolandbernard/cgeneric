// test:

#include <assert.h>

#define MAX(A, B) ((A) < (B) ? (B) : (A))
#define COMBINE(A, B) MAX(A, B)

#include "segment-tree/tree.c"

#define N 1000
    
int main() {
    int* tree = createSegmentTreeInt(N);
    for (size_t i = 0; i < N; i++) {
        setInSegmentTreeInt(tree, N, i, 2*i);
        assert(querySegmentTreeInt(tree, N, 0, i + 1) == 2*(int)i);
    }
    FREE(tree);
    return 0;
}

