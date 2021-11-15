
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

bool TYPED(insertIntoHashSet)(TYPED(HashSet)* set, TYPE key);

bool TYPED(hasInHashSet)(TYPED(HashSet)* set, TYPE key);

void TYPED(deleteFromHashSet)(TYPED(HashSet)* set, TYPE key);

typedef struct TYPED(HashSetIterator) TYPED(HashSetIterator);

struct TYPED(HashSetIterator) {
    TYPED(HashSet)* set;
    size_t i;
};

TYPED(HashSetIterator) TYPED(getHashSetIterator)(TYPED(HashSet)* set);

bool TYPED(hasNextHashSet)(TYPED(HashSetIterator)* iter);

TYPE TYPED(getNextHashSet)(TYPED(HashSetIterator)* iter);

