// test:

#include <assert.h>

#include "array.h"

#include "radix-sort/sort.c"

int main() {
    radixSortTest(array2, LEN(array2));
    for (size_t i = 1; i < LEN(array2); i++) {
        assert(compareTest(array2[i - 1], array2[i]));
    }
    return 0;
}

