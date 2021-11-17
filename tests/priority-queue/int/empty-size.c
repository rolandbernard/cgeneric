// test:

#include <assert.h>

#include "priority-queue/priority-queue.c"

int main() {
    PriorityQueueInt list;
    initPriorityQueueInt(&list);
    assert(sizeOfPriorityQueueInt(&list) == 0);
    deinitPriorityQueueInt(&list);
    return 0;
}
