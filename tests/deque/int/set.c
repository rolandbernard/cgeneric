// test:

#include <assert.h>

#include "deque/deque.c"

int main() {
    DequeInt list;
    initDequeInt(&list);
    for (size_t i = 0; i < 100; i++) {
        pushToDequeInt(&list, 0);
    }
    for (size_t i = 0; i < 100; i++) {
        setInDequeInt(&list, i, 2*i);
        assert(getFromDequeInt(&list, i) == 2 * (int)i);
    }
    deinitDequeInt(&list);
    return 0;
}

