
#include <stddef.h>
#include <stdbool.h>

#include "default.h"

typedef struct TYPED(HashSet) TYPED(HashSet);

struct TYPED(HashSet) {
    size_t count;
    size_t capacity;
    TYPE* keys;
#ifndef IMPLICIT_STATE
    char* state;
#endif
};

void TYPED(initHashSet)(TYPED(HashSet)* set);

void TYPED(deinitHashSet)(TYPED(HashSet)* set);

size_t TYPED(sizeOfHashSet)(TYPED(HashSet)* set);

void TYPED(reserveHashSet)(TYPED(HashSet)* set, size_t size);

void TYPED(insertIntoHashSet)(TYPED(HashSet)* set, TYPE key);

bool TYPED(hasInHashSet)(TYPED(HashSet)* set, TYPE key);

void TYPED(deleteFromHashSet)(TYPED(HashSet)* set, TYPE key);

