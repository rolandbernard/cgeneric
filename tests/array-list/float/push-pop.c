// test:

#include <assert.h>

#define TYPE double
#define TYPED(NAME) NAME ## Double

#include "array-list/array-list.c"

int main() {
    ArrayListDouble list;
    initArrayListDouble(&list);
    for (int i = 0; i < 1000; i++) {
        pushToArrayListDouble(&list, (double)i / 2);
        assert(sizeOfArrayListDouble(&list) == (size_t)i + 1);
        assert(getFromArrayListDouble(&list, i) == (double)i / 2);
    }
    for (int i = 999; i >= 0; i--) {
        double val = popFromArrayListDouble(&list);
        assert(sizeOfArrayListDouble(&list) == (size_t)i);
        assert(val == (double)i / 2);
    }
    deinitArrayListDouble(&list);
    return 0;
}

