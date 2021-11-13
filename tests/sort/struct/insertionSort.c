// test:

#include <assert.h>

#include "array.h"

#include "sort/sort.c"

int main() {
    insertionSortTest(array0, LEN(array0));
    for (size_t i = 1; i < LEN(array0); i++) {
        assert(compareTest(array0[i - 1], array0[i]));
    }
    return 0;
}

