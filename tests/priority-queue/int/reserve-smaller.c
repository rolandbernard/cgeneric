// test:

#include <assert.h>

#include "priority-queue/priority-queue.c"

int main() {
    PriorityQueueInt list;
    initPriorityQueueInt(&list);
    for (int i = 0; i < 500; i++) {
        pushToPriorityQueueInt(&list, i);
    }
    reservePriorityQueueInt(&list, 50);
    assert(list.capacity >= 500);
    assert(sizeOfPriorityQueueInt(&list) == 500);
    deinitPriorityQueueInt(&list);
    return 0;
}

