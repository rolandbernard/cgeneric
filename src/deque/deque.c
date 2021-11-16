
#include "deque.h"
#include <assert.h>
#include <stddef.h>

void TYPED(initDeque)(TYPED(Deque)* queue) {
    queue->data = NULL;
    queue->capacity = 0;
    queue->front = 0;
    queue->back = 0;
}

void TYPED(deinitDeque)(TYPED(Deque)* queue) {
    FREE(queue->data);
    TYPED(initDeque)(queue);
}

static void TYPED(resizeDeque)(TYPED(Deque)* queue, size_t size) {
    if (size < queue->capacity && (queue->front >= size || queue->back >= size)) {
        if (queue->back < queue->front) {
            for (size_t i = queue->front; i < queue->capacity; i++) {
                queue->data[i + size - queue->capacity] = queue->data[i];
            }
            queue->front -= queue->capacity - size;
        } else {
            for (size_t i = queue->front; i < queue->back; i++) {
                queue->data[i - queue->front] = queue->data[i];
            }
            queue->back -= queue->front;
            queue->front = 0;
        }
    }
    queue->data = REALLOC(TYPE, queue->data, size);
    if (size > queue->capacity && queue->back < queue->front) {
        size_t new_back = queue->capacity;
        for (size_t i = 0; i < queue->back; i++) {
            queue->data[new_back] = queue->data[i];
            new_back = (new_back + 1) % size;
        }
        queue->back = new_back;
    }
    queue->capacity = size;
}

static void TYPED(growDeque)(TYPED(Deque)* queue) {
    TYPED(resizeDeque)(queue, GROWTH_FUNCTION(queue->capacity));
}

static void TYPED(tryShrinkingDeque)(TYPED(Deque)* queue) {
    if (queue->capacity != 0) {
        size_t count = (queue->back + queue->capacity - queue->front) % queue->capacity;
        if (SHOULD_SHRINK(count, queue->capacity)) {
            TYPED(resizeDeque)(queue, SHRINK_FUNCTION(queue->capacity));
        }
    }
}

size_t TYPED(sizeOfDeque)(TYPED(Deque)* queue) {
    if (queue->capacity == 0) {
        return 0;
    } else {
        return (queue->back + queue->capacity - queue->front) % queue->capacity;
    }
}

void TYPED(reserveDeque)(TYPED(Deque)* queue, size_t size) {
    if (size > queue->capacity) {
        TYPED(resizeDeque)(queue, size);
    }
}

void TYPED(pushToDeque)(TYPED(Deque)* queue, TYPE element) {
    if (queue->capacity == 0 || (queue->back + 1) % queue->capacity == queue->front) {
        TYPED(growDeque)(queue);
    }
    queue->data[queue->back] = element;
    queue->back = (queue->back + 1) % queue->capacity;
}

TYPE TYPED(popFromDeque)(TYPED(Deque)* queue) {
    assert(queue->capacity != 0);
    queue->back = (queue->capacity + queue->back - 1) % queue->capacity;
    TYPE ret = queue->data[queue->back];
    TYPED(tryShrinkingDeque)(queue);
    return ret;
}

void TYPED(pushFrontToDeque)(TYPED(Deque)* queue, TYPE element) {
    if (
        queue->capacity == 0
        || (queue->capacity + queue->front - 1) % queue->capacity == queue->back
    ) {
        TYPED(growDeque)(queue);
    }
    queue->front = (queue->capacity + queue->front - 1) % queue->capacity;
    queue->data[queue->front] = element;
}

TYPE TYPED(popFrontFromDeque)(TYPED(Deque)* queue) {
    assert(queue->capacity != 0);
    TYPE ret = queue->data[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    TYPED(tryShrinkingDeque)(queue);
    return ret;
}

TYPE TYPED(getFromDeque)(TYPED(Deque)* queue, size_t i) {
    assert(queue->capacity != 0);
    return queue->data[(queue->front + i) % queue->capacity];
}

void TYPED(setInDeque)(TYPED(Deque)* queue, size_t i, TYPE element) {
    assert(queue->capacity != 0);
    queue->data[(queue->front + i) % queue->capacity] = element;
}

TYPED(DequeIterator) TYPED(getDequeIterator)(TYPED(Deque)* queue) {
    TYPED(DequeIterator) ret = {
        .queue = queue,
        .i = queue->front,
    };
    return ret;
}

bool TYPED(hasNextDeque)(TYPED(DequeIterator)* iter) {
    return iter->i != iter->queue->back;
}

TYPE TYPED(getNextDeque)(TYPED(DequeIterator)* iter) {
    TYPE ret = iter->queue->data[iter->i];
    iter->i = (iter->i + 1) % iter->queue->capacity;
    return ret;
}

