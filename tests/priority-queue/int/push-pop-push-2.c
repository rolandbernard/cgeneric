// test:

#include <assert.h>

#define LESS_EQUAL(A, B) (A <= B)

#include "priority-queue/priority-queue.c"

int main() {
    PriorityQueueInt list;
    initPriorityQueueInt(&list);
    for (int i = 0; i < 1000; i++) {
        pushToPriorityQueueInt(&list, 1000 - 2 * i);
        assert(sizeOfPriorityQueueInt(&list) == (size_t)i + 1);
    }
    for (int i = 0; i < 1000; i++) {
        int val = popFromPriorityQueueInt(&list);
        assert(sizeOfPriorityQueueInt(&list) == 999 - (size_t)i);
        assert(val == 2 * i - 998);
    }
    deinitPriorityQueueInt(&list);
    return 0;
}

