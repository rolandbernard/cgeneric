// test:

#include <assert.h>

#include "array.h"

#include "sort/sort.c"

int main() {
    for (size_t i = 0; i < LEN(array2); i++) {
        array2[i].a = rand() % 100;
        array2[i].b = array2[i].a;
        array2[i].i = i;
    }
    stableSortTest(array2, LEN(array2));
    for (size_t i = 1; i < LEN(array2); i++) {
        assert(compareTest(array2[i - 1], array2[i]));
        if (compareTest(array2[i - 1], array2[i]) && compareTest(array2[i], array2[i - 1])) {
            assert(array2[i - 1].i < array2[i].i);
        }
    }
    return 0;
}

