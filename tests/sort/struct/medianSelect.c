// test:

#include <assert.h>

#include "array.h"

#include "sort/sort.c"

int main() {
    size_t k = LEN(array1)/2;
    medianSelectTest(array1, k, LEN(array1));
    for (size_t i = 0; i < k; i++) {
        assert(compareTest(array1[i], array1[k]));
    }
    for (size_t i = k + 1; i < LEN(array1); i++) {
        assert(compareTest(array1[k], array1[i]));
    }
    return 0;
}

