// test:

#include <assert.h>

#include "array-list/array-list.c"

int main() {
    ArrayListInt list;
    initArrayListInt(&list);
    reserveArrayListInt(&list, 50000);
    assert(list.capacity >= 50000);
    shrinkToFitArrayListInt(&list);
    assert(list.capacity == 0);
    assert(list.data == NULL);
    deinitArrayListInt(&list);
    return 0;
}

