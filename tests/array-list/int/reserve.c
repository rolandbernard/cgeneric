// test:

#include <assert.h>

#include "array-list/array-list.c"

int main() {
    ArrayListInt list;
    initArrayListInt(&list);
    reserveArrayListInt(&list, 50000);
    assert(list.data != NULL);
    assert(list.capacity >= 50000);
    deinitArrayListInt(&list);
    return 0;
}

