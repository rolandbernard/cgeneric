// test:

#include <assert.h>
#include <string.h>

#define TYPE const char*
#define TYPED(NAME) NAME ## Test
#define LESS_EQUAL(A, B) (strcmp(A, B) <= 0)

#include "sort/sort.c"

#include "array.h"

int main() {
    size_t k = LEN(array1)/2;
    quickSelectTest(array1, k, LEN(array1));
    for (size_t i = 0; i < k; i++) {
        assert(strcmp(array1[i], array1[k]) <= 0);
    }
    for (size_t i = k + 1; i < LEN(array1); i++) {
        assert(strcmp(array1[k], array1[i]) <= 0);
    }
    return 0;
}

