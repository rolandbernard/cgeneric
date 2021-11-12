// test:

#include <assert.h>
#include <string.h>

#define TYPE const char*
#define TYPED(NAME) NAME ## Test
#define LESS_EQUAL(A, B) (strcmp(A, B) <= 0)

#include "sort/sort.c"

#include "array.h"

int main() {
    insertionSortTest(array0, LEN(array0));
    for (size_t i = 1; i < LEN(array0); i++) {
        assert(strcmp(array0[i - 1], array0[i]) <= 0);
    }
    return 0;
}

