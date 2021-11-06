// test:

#include <assert.h>

#include "array-list/array-list.c"

int main() {
    ArrayListInt list;
    initArrayListInt(&list);
    for (size_t i = 0; i < 1000; i++) {
        pushToArrayListInt(&list, 2*i);
        assert(sizeOfArrayListInt(&list) == i + 1);
        assert(getFromArrayListInt(&list, i) == 2*(int)i);
    }
    deinitArrayListInt(&list);
    return 0;
}

