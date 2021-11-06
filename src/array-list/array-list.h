
#include <stddef.h>

#include "default.h"

typedef struct TYPED(ArrayList) TYPED(ArrayList);

struct TYPED(ArrayList) {
    TYPE* data;
    size_t count;
    size_t capacity;
};

void TYPED(initArrayList)(TYPED(ArrayList)* list);

void TYPED(deinitArrayList)(TYPED(ArrayList)* list);

size_t TYPED(sizeOfArrayList)(TYPED(ArrayList)* list);

void TYPED(reserveArrayList)(TYPED(ArrayList)* list, size_t size);

void TYPED(shrinkToFitArrayList)(TYPED(ArrayList)* list);

void TYPED(resizeArrayList)(TYPED(ArrayList)* list, size_t size);

void TYPED(pushToArrayList)(TYPED(ArrayList)* list, TYPE element);

TYPE TYPED(popFromArrayList)(TYPED(ArrayList)* list);

TYPE TYPED(getFromArrayList)(TYPED(ArrayList)* list, size_t i);

void TYPED(setInArrayList)(TYPED(ArrayList)* list, size_t i, TYPE element);

