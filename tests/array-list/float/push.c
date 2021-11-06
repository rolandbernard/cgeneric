// test:

#include <assert.h>

#define TYPE double
#define TYPED(NAME) NAME ## Double

#include "array-list/array-list.c"

int main() {
    ArrayListDouble list;
    initArrayListDouble(&list);
    for (size_t i = 0; i < 1000; i++) {
        pushToArrayListDouble(&list, (double)i / 2);
        assert(sizeOfArrayListDouble(&list) == i + 1);
        assert(getFromArrayListDouble(&list, i) == (double)i / 2);
    }
    deinitArrayListDouble(&list);
    return 0;
}

