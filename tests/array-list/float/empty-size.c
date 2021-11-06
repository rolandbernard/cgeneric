// test:

#include <assert.h>

#define TYPE double
#define TYPED(NAME) NAME ## Double

#include "array-list/array-list.c"

int main() {
    ArrayListDouble list;
    initArrayListDouble(&list);
    assert(sizeOfArrayListDouble(&list) == 0);
    deinitArrayListDouble(&list);
    return 0;
}
