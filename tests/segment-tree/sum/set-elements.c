// test:

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

#define TYPE unsigned int

#include "segment-tree/tree.c"

#define N 1000

unsigned int flat[N];

unsigned int simpleSum(size_t i, size_t j) {
    unsigned int sum = 0;
    for (size_t k = i; k < j; k++) {
        sum += flat[k];
    }
    return sum;
}
    
int main() {
    unsigned int* tree = createSegmentTreeInt(N);
    for (size_t i = 0; i < 5*N; i++) {
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

