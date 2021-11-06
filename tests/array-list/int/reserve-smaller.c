// test:

#include <assert.h>

#include "array-list/array-list.c"

int main() {
    ArrayListInt list;
    initArrayListInt(&list);
    resizeArrayListInt(&list, 500);
    reserveArrayListInt(&list, 50);
    assert(list.capacity >= 500);
    assert(sizeOfArrayListInt(&list) == 500);
    deinitArrayListInt(&list);
    return 0;
}

