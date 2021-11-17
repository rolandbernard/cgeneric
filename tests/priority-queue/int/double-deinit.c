// test:

#include <assert.h>

#include "priority-queue/priority-queue.c"

int main() {
    PriorityQueueInt list;
    initPriorityQueueInt(&list);
    deinitPriorityQueueInt(&list);
    deinitPriorityQueueInt(&list); // This must not give an error
    assert(list.data == NULL);
    return 0;
}
