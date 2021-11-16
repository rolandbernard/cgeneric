// test:

#include <assert.h>

#include "deque/deque.c"

int main() {
    DequeInt list;
    initDequeInt(&list);
    for (size_t i = 0; i < 1000; i++) {
        pushToDequeInt(&list, 2*i);
        assert(sizeOfDequeInt(&list) == i + 1);
        assert(getFromDequeInt(&list, i) == 2*(int)i);
    }
    deinitDequeInt(&list);
    return 0;
}

