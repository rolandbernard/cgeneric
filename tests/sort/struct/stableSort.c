// test:

#include <assert.h>

#include "array.h"

#include "sort/sort.c"

int main() {
    for (size_t i = 0; i < LEN(array1); i++) {
        array1[i].a = rand() % 100;
        array1[i].b = array1[i].a;
        array1[i].i = i;
    }
    stableSortTest(array1, LEN(array1));
    for (size_t i = 1; i < LEN(array1); i++) {
        assert(compareTest(array1[i - 1], array1[i]));
        if (compareTest(array1[i - 1], array1[i]) && compareTest(array1[i], array1[i - 1])) {
            assert(array1[i - 1].i < array1[i].i);
        }
    }
    return 0;
}

