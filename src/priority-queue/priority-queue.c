
#include <assert.h>
#include <stddef.h>

#include "priority-queue.h"

void TYPED(initPriorityQueue)(TYPED(PriorityQueue)* queue) {
    queue->data = NULL;
    queue->count = 0;
    queue->capacity = 0;
}

void TYPED(deinitPriorityQueue)(TYPED(PriorityQueue)* queue) {
    FREE(queue->data);
    TYPED(initPriorityQueue)(queue);
}

static void TYPED(swapPriorityQueue)(TYPE* array, size_t i, size_t j) {
    TYPE tmp = array[i];
    array[i] = array[j];
    array[j] = tmp;
}

static void TYPED(heapifyUpPriorityQueue)(TYPE* array, size_t i) {
    if (i != 0) {
        size_t parent = (i + 1) / 2 - 1;
        if (!LESS_EQUAL(array[parent], array[i])) {
            TYPED(swapPriorityQueue)(array, parent, i);
            TYPED(heapifyUpPriorityQueue)(array, parent);
        }
    }
}

static void TYPED(heapifyPriorityQueue)(TYPE* array, size_t i, size_t size) {
    size_t left = 2 * (i + 1) - 1;
    size_t right = 2 * (i + 1);
    size_t max = i;
    if (left < size && !LESS_EQUAL(array[max], array[left])) {
        max = left;
    }
    if (right < size && !LESS_EQUAL(array[max], array[right])) {
        max = right;
    }
    if (max != i) {
        TYPED(swapPriorityQueue)(array, max, i);
        TYPED(heapifyPriorityQueue)(array, max, size);
    }
}

static void TYPED(resizePriorityQueue)(TYPED(PriorityQueue)* queue, size_t size) {
    queue->capacity = size;
    queue->data = REALLOC(TYPE, queue->data, queue->capacity);
}

static void TYPED(growPriorityQueue)(TYPED(PriorityQueue)* queue) {
    TYPED(resizePriorityQueue)(queue, GROWTH_FUNCTION(queue->capacity));
}

static void TYPED(tryShrinkingPriorityQueue)(TYPED(PriorityQueue)* queue) {
    if (queue->capacity != 0) {
        if (SHOULD_SHRINK(queue->count, queue->capacity)) {
            TYPED(resizePriorityQueue)(queue, SHRINK_FUNCTION(queue->capacity));
        }
    }
}

size_t TYPED(sizeOfPriorityQueue)(TYPED(PriorityQueue)* queue) {
    return queue->count;
}

void TYPED(reservePriorityQueue)(TYPED(PriorityQueue)* queue, size_t size) {
    if (size > queue->capacity) {
        TYPED(resizePriorityQueue)(queue, size);
    }
}

TYPE TYPED(firstPriorityQueue)(TYPED(PriorityQueue)* queue) {
    return queue->data[0];
}

TYPE TYPED(popFromPriorityQueue)(TYPED(PriorityQueue)* queue) {
    TYPE ret = queue->data[0];
    queue->count--;
    queue->data[0] = queue->data[queue->count];
    TYPED(heapifyPriorityQueue)(queue->data, 0, queue->count);
    TYPED(tryShrinkingPriorityQueue)(queue);
    return ret;
}

void TYPED(pushToPriorityQueue)(TYPED(PriorityQueue)* queue, TYPE element) {
    if (queue->count == queue->capacity) {
        TYPED(growPriorityQueue)(queue);
    }
    queue->data[queue->count] = element;
    TYPED(heapifyUpPriorityQueue)(queue->data, queue->count);
    queue->count++;
}

static void TYPED(buildPriorityQueue)(TYPE* array, size_t size, size_t from, size_t to) {
    for (size_t i = from; i <= to; i++) {
        TYPED(heapifyPriorityQueue)(array, i, size);
    }
    if (from < to) {
        TYPED(buildPriorityQueue)(array, size, (from + 1) / 2 - 1, (to + 1) / 2 - 1);
    }
}

void TYPED(pushAllToPriorityQueue)(TYPED(PriorityQueue)* queue, TYPE* elements, size_t n) {
    TYPED(reservePriorityQueue)(queue, queue->count + n);
    for (size_t i = 0; i < n; i++) {
        queue->data[queue->count + i] = elements[i];
    }
    TYPED(buildPriorityQueue)(queue->data, queue->count, queue->count, queue->count + n);
    queue->count += n;
}

