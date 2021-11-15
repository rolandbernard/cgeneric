// test:

#include <assert.h>

#include "linked-list/linked-list.c"

int main() {
    LinkedListInt list;
    initLinkedListInt(&list);
    for (int i = 0; i < 1000; i++) {
        pushToLinkedListInt(&list, 2*i);
        assert(sizeOfLinkedListInt(&list) == (size_t)i + 1);
        assert(getFromLinkedListInt(&list, i) == 2*i);
    }
    for (int i = 999; i >= 0; i--) {
        int val = popFromLinkedListInt(&list);
        assert(sizeOfLinkedListInt(&list) == (size_t)i);
        assert(val == 2*i);
    }
    deinitLinkedListInt(&list);
    return 0;
}

