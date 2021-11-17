// test:

#include <assert.h>

#include "priority-queue/priority-queue.c"

int main() {
    PriorityQueueInt list;
    initPriorityQueueInt(&list);
    assert(list.count == 0);
    assert(list.capacity == 0);
    assert(list.data == NULL);
    deinitPriorityQueueInt(&list);
    return 0;
}

