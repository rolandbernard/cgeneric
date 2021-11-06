// test:

#include <assert.h>

#define TYPE double
#define TYPED(NAME) NAME ## Double

#include "array-list/array-list.c"

int main() {
    ArrayListDouble list;
    initArrayListDouble(&list);
    reserveArrayListDouble(&list, 50000);
    assert(list.data != NULL);
    assert(list.capacity >= 50000);
    deinitArrayListDouble(&list);
    return 0;
}

