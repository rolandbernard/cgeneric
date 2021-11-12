// test:

#include <assert.h>

#define LESS_EQUAL(A, B) (A <= B)

#include "sort/sort.c"

#include "array.h"

int main() {
    sortInt(array2, LEN(array2));
    for (size_t i = 1; i < LEN(array2); i++) {
        assert(array2[i - 1] <= array2[i]);
    }
    return 0;
}

