// test:

#include <assert.h>

#include "array-list/array-list.c"

int main() {
    ArrayListInt list;
    initArrayListInt(&list);
    resizeArrayListInt(&list, 5000);
    assert(list.data != NULL);
    assert(sizeOfArrayListInt(&list) == 5000);
    deinitArrayListInt(&list);
    return 0;
}

