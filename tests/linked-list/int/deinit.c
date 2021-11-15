// test:

#include <assert.h>

#include "linked-list/linked-list.c"

int main() {
    LinkedListInt list;
    initLinkedListInt(&list);
    pushToLinkedListInt(&list, 42);
    deinitLinkedListInt(&list);
    return 0;
}
