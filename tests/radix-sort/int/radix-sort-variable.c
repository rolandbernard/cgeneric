// test:

#include <assert.h>

#define REVERSED_KEYS
#define VARIABLE_LENGTH
#define LENGTH(VALUE) lengthOfInt(VALUE)

int lengthOfInt(unsigned int n) {
    if (n == 0) {
        return 0;
    } else {
        return  4 - __builtin_clz(n) / 8;
    }
}

#include "radix-sort/sort.c"

#include "array.h"

int main() {
    radixSortInt(array2, LEN(array2));
    for (size_t i = 1; i < LEN(array2); i++) {
        assert(array2[i - 1] <= array2[i]);
    }
    return 0;
}

