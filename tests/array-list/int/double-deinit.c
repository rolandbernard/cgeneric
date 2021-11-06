// test:

#include <assert.h>

#include "array-list/array-list.c"

int main() {
    ArrayListInt list;
    initArrayListInt(&list);
    deinitArrayListInt(&list);
    deinitArrayListInt(&list); // This must not give an error
    assert(list.data == NULL);
    return 0;
}
