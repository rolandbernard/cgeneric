// test:

#include <assert.h>

#include "array-list/array-list.c"

int main() {
    ArrayListInt list;
    initArrayListInt(&list);
    assert(list.count == 0);
    assert(list.capacity == 0);
    assert(list.data == NULL);
    deinitArrayListInt(&list);
    return 0;
}

