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
    for (int i = 0; i < 500; i++) {
        int val = popFrontFromLinkedListInt(&list);
        assert(sizeOfLinkedListInt(&list) == 999 - (size_t)i);
        assert(val == 2*i);
    }
    for (int i = 0; i < 500; i++) {
        pushFrontToLinkedListInt(&list, 2*i);
        assert(sizeOfLinkedListInt(&list) == (size_t)i + 501);
        assert(getFromLinkedListInt(&list, 0) == 2*i);
    }
    for (int i = 499; i >= 0; i--) {
        int val = popFrontFromLinkedListInt(&list);
        assert(sizeOfLinkedListInt(&list) == 500 + (size_t)i);
        assert(val == 2*i);
    }
    deinitLinkedListInt(&list);
    return 0;
}

