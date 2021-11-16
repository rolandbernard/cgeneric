// test:

#include <assert.h>

#include "deque/deque.c"

int main() {
    DequeInt list;
    initDequeInt(&list);
    for (int i = 0; i < 1000; i++) {
        pushToDequeInt(&list, 2*i);
        assert(sizeOfDequeInt(&list) == (size_t)i + 1);
        assert(getFromDequeInt(&list, i) == 2*i);
    }
    for (int i = 999; i >= 0; i--) {
        int val = popFromDequeInt(&list);
        assert(sizeOfDequeInt(&list) == (size_t)i);
        assert(val == 2*i);
    }
    deinitDequeInt(&list);
    return 0;
}

