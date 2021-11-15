// test:

#include <assert.h>

#include "linked-list/linked-list.c"

int main() {
    LinkedListInt list;
    initLinkedListInt(&list);
    deinitLinkedListInt(&list);
    deinitLinkedListInt(&list); // This must not give an error
    return 0;
}
