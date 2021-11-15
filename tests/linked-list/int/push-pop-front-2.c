// test:

#include <assert.h>

#include "linked-list/linked-list.c"

int main() {
    LinkedListInt list;
    initLinkedListInt(&list);
    // []
    pushToLinkedListInt(&list, 12);
    pushToLinkedListInt(&list, 13);
    pushToLinkedListInt(&list, 14);
    pushToLinkedListInt(&list, 15);
    pushToLinkedListInt(&list, 16);
    // [12, 13, 14, 15, 16]
    assert(popFrontFromLinkedListInt(&list) == 12);
    assert(popFromLinkedListInt(&list) == 16);
    // [13, 14, 15]
    pushFrontToLinkedListInt(&list, 20);
    pushFrontToLinkedListInt(&list, 21);
    pushFrontToLinkedListInt(&list, 22);
    // [22, 21, 20, 13, 14, 15]
    pushToLinkedListInt(&list, 30);
    pushToLinkedListInt(&list, 31);
    pushToLinkedListInt(&list, 32);
    // [22, 21, 20, 13, 14, 15, 30, 31, 32]
    assert(popFromLinkedListInt(&list) == 32);
    assert(popFromLinkedListInt(&list) == 31);
    // [22, 21, 20, 13, 14, 15, 30]
    assert(popFrontFromLinkedListInt(&list) == 22);
    assert(popFrontFromLinkedListInt(&list) == 21);
    // [20, 13, 14, 15, 30]
    pushToLinkedListInt(&list, 40);
    pushFrontToLinkedListInt(&list, 41);
    // [41, 20, 13, 14, 15, 30, 40]
    assert(popFromLinkedListInt(&list) == 40);
    assert(popFromLinkedListInt(&list) == 30);
    assert(popFromLinkedListInt(&list) == 15);
    assert(popFromLinkedListInt(&list) == 14);
    assert(popFromLinkedListInt(&list) == 13);
    // [41, 20]
    assert(popFrontFromLinkedListInt(&list) == 41);
    assert(popFrontFromLinkedListInt(&list) == 20);
    // []
    deinitLinkedListInt(&list);
    return 0;
}

