// test:

#include <assert.h>

#include "deque/deque.c"

int main() {
    DequeInt list;
    initDequeInt(&list);
    pushToDequeInt(&list, 42);
    assert(list.data != NULL);
    deinitDequeInt(&list);
    assert(list.data == NULL);
    return 0;
}
