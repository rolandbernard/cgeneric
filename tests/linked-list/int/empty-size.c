// test:

#include <assert.h>

#include "linked-list/linked-list.c"

int main() {
    LinkedListInt list;
    initLinkedListInt(&list);
    assert(sizeOfLinkedListInt(&list) == 0);
    deinitLinkedListInt(&list);
    return 0;
}
