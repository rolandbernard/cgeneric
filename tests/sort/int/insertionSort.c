// test:

#include <assert.h>

#define LESS_EQUAL(A, B) (A <= B)

#include "sort/sort.c"

#include "array.h"

int main() {
    insertionSortInt(array0, LEN(array0));
    for (size_t i = 1; i < LEN(array0); i++) {
        assert(array0[i - 1] <= array0[i]);
    }
    return 0;
}

