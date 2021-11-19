// test:

#include <assert.h>
#include <string.h>

#define TYPE const char*
#define TYPED(NAME) NAME ## Test
#define LESS_EQUAL(A, B) (strcmp(A, B) <= 0)

#include "sort/sort.c"

#include "array.h"

int main() {
    quickSortTest(array1, LEN(array1));
    for (size_t i = 1; i < LEN(array1); i++) {
        assert(strcmp(array1[i - 1], array1[i]) <= 0);
    }
    return 0;
}

