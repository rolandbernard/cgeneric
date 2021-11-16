// test:

#include <assert.h>

#include "deque/deque.c"

int main() {
    DequeInt list;
    initDequeInt(&list);
    initDequeInt(&list);
    initDequeInt(&list); // This must not give an error
    assert(list.data == NULL);
    return 0;
}
