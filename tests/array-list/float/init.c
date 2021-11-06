// test:

#include <assert.h>

#define TYPE double
#define TYPED(NAME) NAME ## Double

#include "array-list/array-list.c"

int main() {
    ArrayListDouble list;
    initArrayListDouble(&list);
    assert(list.count == 0);
    assert(list.capacity == 0);
    assert(list.data == NULL);
    deinitArrayListDouble(&list);
    return 0;
}

