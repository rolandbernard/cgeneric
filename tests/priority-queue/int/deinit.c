// test:

#include <assert.h>

#include "priority-queue/priority-queue.c"

int main() {
    PriorityQueueInt list;
    initPriorityQueueInt(&list);
    pushToPriorityQueueInt(&list, 42);
    assert(list.data != NULL);
    deinitPriorityQueueInt(&list);
    assert(list.data == NULL);
    return 0;
}
