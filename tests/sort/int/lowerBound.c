// test:

#include <assert.h>

#define LESS_EQUAL(A, B) (A <= B)

#include "sort/sort.c"

int sorted[] = { 0, 0, 1, 2, 2, 6, 6, 6, 8, 8 };

#define LEN(A) (sizeof(A)/sizeof(A[0]))

int main() {
    assert(lowerBoundInt(sorted, LEN(sorted), -1) == 0);
    assert(lowerBoundInt(sorted, LEN(sorted), 0) == 0);
    assert(lowerBoundInt(sorted, LEN(sorted), 1) == 2);
    assert(lowerBoundInt(sorted, LEN(sorted), 2) == 3);
    assert(lowerBoundInt(sorted, LEN(sorted), 3) == 5);
    assert(lowerBoundInt(sorted, LEN(sorted), 4) == 5);
    assert(lowerBoundInt(sorted, LEN(sorted), 5) == 5);
    assert(lowerBoundInt(sorted, LEN(sorted), 6) == 5);
    assert(lowerBoundInt(sorted, LEN(sorted), 7) == 8);
    assert(lowerBoundInt(sorted, LEN(sorted), 8) == 8);
    assert(lowerBoundInt(sorted, LEN(sorted), 9) == 10);
    return 0;
}

