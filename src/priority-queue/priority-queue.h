
#include <stddef.h>
#include <stdbool.h>

#include "default.h"

typedef struct TYPED(PriorityQueue) TYPED(PriorityQueue);

struct TYPED(PriorityQueue) {
    TYPE* data;
    size_t capacity;
    size_t count;
};

void TYPED(initPriorityQueue)(TYPED(PriorityQueue)* queue);

void TYPED(deinitPriorityQueue)(TYPED(PriorityQueue)* queue);

size_t TYPED(sizeOfPriorityQueue)(TYPED(PriorityQueue)* queue);

void TYPED(reservePriorityQueue)(TYPED(PriorityQueue)* queue, size_t size);

TYPE TYPED(firstPriorityQueue)(TYPED(PriorityQueue)* queue);

TYPE TYPED(popFromPriorityQueue)(TYPED(PriorityQueue)* queue);

void TYPED(pushToPriorityQueue)(TYPED(PriorityQueue)* queue, TYPE element);

void TYPED(pushAllToPriorityQueue)(TYPED(PriorityQueue)* queue, TYPE* elements, size_t n);

