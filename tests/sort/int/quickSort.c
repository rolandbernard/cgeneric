// test:

#include <assert.h>

#define LESS_EQUAL(A, B) (A <= B)

#include "sort/sort.c"

#include "array.h"

int main() {
    quickSortInt(array1, LEN(array1));
    for (size_t i = 1; i < LEN(array1); i++) {
        assert(array1[i - 1] <= array1[i]);
    }
    return 0;
}

