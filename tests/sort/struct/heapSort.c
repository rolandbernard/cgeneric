// test:

#include <assert.h>

#include "array.h"

#include "sort/sort.c"

int main() {
    heapSortTest(array1, LEN(array1));
    for (size_t i = 1; i < LEN(array1); i++) {
        assert(compareTest(array1[i - 1], array1[i]));
    }
    return 0;
}

