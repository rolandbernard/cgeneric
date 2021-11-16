// test:

#include <assert.h>

#include "deque/deque.c"

int main() {
    DequeInt list;
    initDequeInt(&list);
    assert(sizeOfDequeInt(&list) == 0);
    deinitDequeInt(&list);
    return 0;
}
