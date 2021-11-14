// test:

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

#define MAX(A, B) ((A) < (B) ? (B) : (A))
#define COMBINE(A, B) MAX(A, B)

#include "segment-tree/tree.c"

#define N 1000

int flat[N];

int simpleSum(size_t i, size_t j) {
    int max = 0;
    for (size_t k = i; k < j; k++) {
        max = MAX(max, flat[k]);
    }
    return max;
}
    
int main() {
    int* tree = createSegmentTreeInt(N);
    for (size_t i = 0; i < 25*N; i++) {
        size_t idx = rand() % N;
        flat[idx] = rand();
        setInSegmentTreeInt(tree, N, idx, flat[idx]);
        size_t to = rand() % N;
        size_t from = (to == 0 ? 0 : rand() % to);
        assert(querySegmentTreeInt(tree, N, from, to) == simpleSum(from, to));
    }
    FREE(tree);
    return 0;
}

