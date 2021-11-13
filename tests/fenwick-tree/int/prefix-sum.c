// test:

#include <assert.h>

#include "fenwick-tree/bit.c"

#define N 1000

int tree[N];
    
int main() {
    int sum = 0;
    for (size_t i = 0; i < N; i++) {
        addToBitInt(tree, N, i, 2*i);
        sum += 2*i;
        assert(prefixSumInBitInt(tree, i) == sum);
    }
    return 0;
}

