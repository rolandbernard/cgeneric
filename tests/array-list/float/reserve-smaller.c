// test:

#include <assert.h>

#define TYPE double
#define TYPED(NAME) NAME ## Double

#include "array-list/array-list.c"

int main() {
    ArrayListDouble list;
    initArrayListDouble(&list);
    resizeArrayListDouble(&list, 500);
    reserveArrayListDouble(&list, 50);
    assert(list.capacity >= 500);
    assert(sizeOfArrayListDouble(&list) == 500);
    deinitArrayListDouble(&list);
    return 0;
}

