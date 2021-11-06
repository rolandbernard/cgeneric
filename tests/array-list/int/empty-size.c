// test:

#include <assert.h>

#include "array-list/array-list.c"

int main() {
    ArrayListInt list;
    initArrayListInt(&list);
    assert(sizeOfArrayListInt(&list) == 0);
    deinitArrayListInt(&list);
    return 0;
}
