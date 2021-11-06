// test:

#include <assert.h>

#define TYPE double
#define TYPED(NAME) NAME ## Double

#include "array-list/array-list.c"

int main() {
    ArrayListDouble list;
    initArrayListDouble(&list);
    deinitArrayListDouble(&list);
    deinitArrayListDouble(&list); // This must not give an error
    assert(list.data == NULL);
    return 0;
}
