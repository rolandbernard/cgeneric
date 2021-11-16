// test:

#include <assert.h>

#include "deque/deque.c"

int main() {
    DequeInt list;
    initDequeInt(&list);
    // []
    pushToDequeInt(&list, 12);
    pushToDequeInt(&list, 13);
    pushToDequeInt(&list, 14);
    pushToDequeInt(&list, 15);
    pushToDequeInt(&list, 16);
    // [12, 13, 14, 15, 16]
    assert(popFrontFromDequeInt(&list) == 12);
    assert(popFrontFromDequeInt(&list) == 13);
    // [14, 15, 16]
    pushToDequeInt(&list, 20);
    pushToDequeInt(&list, 21);
    pushToDequeInt(&list, 22);
    pushToDequeInt(&list, 23);
    // [14, 15, 16, 20, 21, 22, 23]
    assert(popFrontFromDequeInt(&list) == 14);
    assert(popFrontFromDequeInt(&list) == 15);
    assert(popFrontFromDequeInt(&list) == 16);
    assert(popFrontFromDequeInt(&list) == 20);
    assert(popFrontFromDequeInt(&list) == 21);
    assert(popFrontFromDequeInt(&list) == 22);
    assert(popFrontFromDequeInt(&list) == 23);
    // []
    deinitDequeInt(&list);
    return 0;
}

