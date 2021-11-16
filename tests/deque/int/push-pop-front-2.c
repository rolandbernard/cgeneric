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
    assert(popFromDequeInt(&list) == 16);
    // [13, 14, 15]
    pushFrontToDequeInt(&list, 20);
    pushFrontToDequeInt(&list, 21);
    pushFrontToDequeInt(&list, 22);
    // [22, 21, 20, 13, 14, 15]
    pushToDequeInt(&list, 30);
    pushToDequeInt(&list, 31);
    pushToDequeInt(&list, 32);
    // [22, 21, 20, 13, 14, 15, 30, 31, 32]
    assert(popFromDequeInt(&list) == 32);
    assert(popFromDequeInt(&list) == 31);
    // [22, 21, 20, 13, 14, 15, 30]
    assert(popFrontFromDequeInt(&list) == 22);
    assert(popFrontFromDequeInt(&list) == 21);
    // [20, 13, 14, 15, 30]
    pushToDequeInt(&list, 40);
    pushFrontToDequeInt(&list, 41);
    // [41, 20, 13, 14, 15, 30, 40]
    assert(popFromDequeInt(&list) == 40);
    assert(popFromDequeInt(&list) == 30);
    assert(popFromDequeInt(&list) == 15);
    assert(popFromDequeInt(&list) == 14);
    assert(popFromDequeInt(&list) == 13);
    // [41, 20]
    assert(popFrontFromDequeInt(&list) == 41);
    assert(popFrontFromDequeInt(&list) == 20);
    // []
    deinitDequeInt(&list);
    return 0;
}

