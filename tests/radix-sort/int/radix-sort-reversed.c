// test:

#include <assert.h>

#define REVERSED_KEYS

#include "radix-sort/sort.c"

#include "array.h"

int main() {
    radixSortInt(array2, LEN(array2));
    for (size_t i = 1; i < LEN(array2); i++) {
        assert(array2[i - 1] <= array2[i]);
    }
    return 0;
}

