// test:

#include <assert.h>

#include "deque/deque.c"

int main() {
    DequeInt list;
    initDequeInt(&list);
    assert(list.capacity == 0);
    assert(list.data == NULL);
    deinitDequeInt(&list);
    return 0;
}

