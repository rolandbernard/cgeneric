// test:

#include <assert.h>

#define TYPE double
#define TYPED(NAME) NAME ## Double

#include "array-list/array-list.c"

int main() {
    ArrayListDouble list;
    initArrayListDouble(&list);
    resizeArrayListDouble(&list, 5000);
    assert(list.data != NULL);
    assert(sizeOfArrayListDouble(&list) == 5000);
    deinitArrayListDouble(&list);
    return 0;
}

