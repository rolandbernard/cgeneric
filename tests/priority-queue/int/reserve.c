// test:

#include <assert.h>

#include "priority-queue/priority-queue.c"

int main() {
    PriorityQueueInt list;
    initPriorityQueueInt(&list);
    reservePriorityQueueInt(&list, 50000);
    assert(list.data != NULL);
    assert(list.capacity >= 50000);
    deinitPriorityQueueInt(&list);
    return 0;
}

