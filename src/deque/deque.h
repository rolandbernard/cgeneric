
#include <stddef.h>
#include <stdbool.h>

#include "default.h"

typedef struct TYPED(Deque) TYPED(Deque);

struct TYPED(Deque) {
    TYPE* data;
    size_t capacity;
    size_t front;
    size_t back;
};

void TYPED(initDeque)(TYPED(Deque)* queue);

void TYPED(deinitDeque)(TYPED(Deque)* queue);

size_t TYPED(sizeOfDeque)(TYPED(Deque)* queue);

void TYPED(reserveDeque)(TYPED(Deque)* queue, size_t size);

void TYPED(pushToDeque)(TYPED(Deque)* queue, TYPE element);

TYPE TYPED(popFromDeque)(TYPED(Deque)* queue);

void TYPED(pushFrontToDeque)(TYPED(Deque)* queue, TYPE element);

TYPE TYPED(popFrontFromDeque)(TYPED(Deque)* queue);

TYPE TYPED(getFromDeque)(TYPED(Deque)* queue, size_t i);

void TYPED(setInDeque)(TYPED(Deque)* queue, size_t i, TYPE element);

typedef struct TYPED(DequeIterator) TYPED(DequeIterator);

struct TYPED(DequeIterator) {
    TYPED(Deque)* queue;
    size_t i;
};

TYPED(DequeIterator) TYPED(getDequeIterator)(TYPED(Deque)* queue);

bool TYPED(hasNextDeque)(TYPED(DequeIterator)* iter);

TYPE TYPED(getNextDeque)(TYPED(DequeIterator)* iter);

