// test:

#include <assert.h>

#include "array-list/array-list.c"

int main() {
    ArrayListInt list;
    initArrayListInt(&list);
    resizeArrayListInt(&list, 100);
    for (size_t i = 0; i < 100; i++) {
        setInArrayListInt(&list, i, 2*i);
        assert(getFromArrayListInt(&list, i) == 2 * (int)i);
    }
    deinitArrayListInt(&list);
    return 0;
}

