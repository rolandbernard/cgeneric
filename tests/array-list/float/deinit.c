// test:

#include <assert.h>

#define TYPE double
#define TYPED(NAME) NAME ## Double

#include "array-list/array-list.c"

int main() {
    ArrayListDouble list;
    initArrayListDouble(&list);
    pushToArrayListDouble(&list, 42.5);
    assert(list.data != NULL);
    deinitArrayListDouble(&list);
    assert(list.data == NULL);
    return 0;
}
