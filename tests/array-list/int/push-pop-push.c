// test:

#include <assert.h>

#include "array-list/array-list.c"

int main() {
    ArrayListInt list;
    initArrayListInt(&list);
    for (int i = 0; i < 1000; i++) {
        pushToArrayListInt(&list, 2*i);
        assert(sizeOfArrayListInt(&list) == (size_t)i + 1);
        assert(getFromArrayListInt(&list, i) == 2*i);
    }
    for (int i = 999; i >= 500; i--) {
        int val = popFromArrayListInt(&list);
        assert(sizeOfArrayListInt(&list) == (size_t)i);
        assert(val == 2*i);
    }
    for (int i = 0; i < 500; i++) {
        pushToArrayListInt(&list, 2*i);
        assert(sizeOfArrayListInt(&list) == 501 + (size_t)i);
        assert(getFromArrayListInt(&list, 500 + i) == 2*i);
    }
    deinitArrayListInt(&list);
    return 0;
}

