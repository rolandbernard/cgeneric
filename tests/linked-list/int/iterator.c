// test:

#include <assert.h>

#include "linked-list/linked-list.c"

int main() {
    LinkedListInt list;
    initLinkedListInt(&list);
    for (size_t i = 0; i < 1000; i++) {
        pushToLinkedListInt(&list, 2*i);
        assert(sizeOfLinkedListInt(&list) == i + 1);
        assert(getFromLinkedListInt(&list, i) == 2*(int)i);
    }
    LinkedListIteratorInt it = getLinkedListIteratorInt(&list);
    size_t i = 0;
    while (hasNextLinkedListInt(&it)) {
        int v = getNextLinkedListInt(&it);
        assert(v == 2*(int)i);
        i++;
    }
    assert(i == 1000);
    deinitLinkedListInt(&list);
    return 0;
}

