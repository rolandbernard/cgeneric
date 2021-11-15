
#include <assert.h>

#include "array-list.h"

void TYPED(initArrayList)(TYPED(ArrayList)* list) {
    list->data = NULL;
    list->count = 0;
    list->capacity = 0;
}

void TYPED(deinitArrayList)(TYPED(ArrayList)* list) {
    FREE(list->data);
    list->data = NULL;
    list->count = 0;
    list->capacity = 0;
}

size_t TYPED(sizeOfArrayList)(TYPED(ArrayList)* list) {
    return list->count;
}

static void TYPED(growArrayList)(TYPED(ArrayList)* list) {
    list->capacity = GROWTH_FUNCTION(list->capacity);
    list->data = REALLOC(TYPE, list->data, list->capacity);
}

static void TYPED(tryShrinkingArrayList)(TYPED(ArrayList)* list) {
    if (SHOULD_SHRINK(list->count, list->capacity)) {
        list->capacity = SHRINK_FUNCTION(list->capacity);
        list->data = REALLOC(TYPE, list->data, list->capacity);
    }
}

void TYPED(reserveArrayList)(TYPED(ArrayList)* list, size_t size) {
    if (size > list->capacity) {
        list->capacity = size;
        list->data = REALLOC(TYPE, list->data, size);
    }
}

void TYPED(shrinkToFitArrayList)(TYPED(ArrayList)* list) {
    list->capacity = list->count;
    list->data = REALLOC(TYPE, list->data, list->capacity);
}

void TYPED(resizeArrayList)(TYPED(ArrayList)* list, size_t size) {
    list->count = size;
    list->capacity = size;
    list->data = REALLOC(TYPE, list->data, size);
}

void TYPED(pushToArrayList)(TYPED(ArrayList)* list, TYPE element) {
    if (list->count == list->capacity) {
        TYPED(growArrayList)(list);
    }
    assert(list->count < list->capacity);
    list->data[list->count] = element;
    list->count++;
}

TYPE TYPED(popFromArrayList)(TYPED(ArrayList)* list) {
    list->count--;
    TYPE ret = list->data[list->count];
    TYPED(tryShrinkingArrayList)(list);
    return ret;
}

TYPE TYPED(getFromArrayList)(TYPED(ArrayList)* list, size_t i) {
    return list->data[i];
}

void TYPED(setInArrayList)(TYPED(ArrayList)* list, size_t i, TYPE element) {
    list->data[i] = element;
}

TYPED(ArrayListIterator) TYPED(getArrayListIterator)(TYPED(ArrayList)* list) {
    TYPED(ArrayListIterator) ret = {
        .list = list,
        .i = 0,
    };
    return ret;
}

bool TYPED(hasNextArrayList)(TYPED(ArrayListIterator)* iter) {
    return iter->i < iter->list->count;
}

TYPE TYPED(getNextArrayList)(TYPED(ArrayListIterator)* iter) {
    TYPE ret = iter->list->data[iter->i];
    iter->i++;
    return ret;
}

