// test:

#include <assert.h>

#define TYPE double
#define TYPED(NAME) NAME ## Double

#include "array-list/array-list.c"

int main() {
    ArrayListDouble list;
    initArrayListDouble(&list);
    resizeArrayListDouble(&list, 100);
    for (size_t i = 0; i < 100; i++) {
        setInArrayListDouble(&list, i, 2*i);
        assert(getFromArrayListDouble(&list, i) == 2 * (int)i);
    }
    deinitArrayListDouble(&list);
    return 0;
}

