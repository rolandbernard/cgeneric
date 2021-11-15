// test:

#include <assert.h>

#include "linked-list/linked-list.c"

int main() {
    LinkedListInt list;
    initLinkedListInt(&list);
    for (size_t i = 0; i < 100; i++) {
        pushToLinkedListInt(&list, 0);
    }
    for (size_t i = 0; i < 100; i++) {
        setInLinkedListInt(&list, i, 2*i);
        assert(getFromLinkedListInt(&list, i) == 2 * (int)i);
    }
    deinitLinkedListInt(&list);
    return 0;
}

