// test:

#include <assert.h>
#include <string.h>

#define TYPE const char*
#define TYPED(NAME) NAME ## Test
#define LESS_EQUAL(A, B) (strcmp(A, B) <= 0)

#include "sort/sort.c"

#include "array.h"

int main() {
    shellSortTest(array2, LEN(array2));
    for (size_t i = 1; i < LEN(array2); i++) {
        assert(strcmp(array2[i - 1], array2[i]) <= 0);
    }
    return 0;
}

