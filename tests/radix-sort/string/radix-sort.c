// test:

#include <assert.h>
#include <string.h>

#define TYPE const char*
#define TYPED(NAME) NAME ## Test
#define VARIABLE_LENGTH
#define LENGTH(V) strlen(V)
#define GET_KEY(V, N) (strlen(V) > N ? V[N] : 0) 

#include "radix-sort/sort.c"

#include "array.h"

int main() {
    radixSortTest(array2, LEN(array2));
    for (size_t i = 1; i < LEN(array2); i++) {
        assert(strcmp(array2[i - 1], array2[i]) <= 0);
    }
    return 0;
}

