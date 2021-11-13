// test:

#include <assert.h>

#define LESS_EQUAL(A, B) (A <= B)

#include "sort/sort.c"

#include "array.h"

int main() {
    size_t k = LEN(array1)/2;
    quickSelectInt(array1, k, LEN(array1));
    for (size_t i = 0; i < k; i++) {
        assert(array1[i] <= array1[k]);
    }
    for (size_t i = k + 1; i < LEN(array1); i++) {
        assert(array1[k] <= array1[i]);
    }
    return 0;
}

