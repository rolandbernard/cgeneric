// test:

#include <assert.h>

#include "array-list/array-list.c"

int main() {
    ArrayListInt list;
    initArrayListInt(&list);
    pushToArrayListInt(&list, 42);
    assert(list.data != NULL);
    deinitArrayListInt(&list);
    assert(list.data == NULL);
    return 0;
}
