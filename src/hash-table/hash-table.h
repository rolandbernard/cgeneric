
#include <stddef.h>
#include <stdbool.h>

#include "default.h"

typedef struct TYPED(HashTable) TYPED(HashTable);

struct TYPED(HashTable) {
    size_t count;
    size_t capacity;
    KEY* keys;
    VALUE* values;
#ifndef IMPLICIT_STATE
    char* state;
#endif
};

void TYPED(initHashTable)(TYPED(HashTable)* table);

void TYPED(deinitHashTable)(TYPED(HashTable)* table);

size_t TYPED(sizeOfHashTable)(TYPED(HashTable)* table);

void TYPED(reserveHashTable)(TYPED(HashTable)* table, size_t size);

void TYPED(putInHashTable)(TYPED(HashTable)* table, KEY key, VALUE value);

VALUE TYPED(getFromHashTable)(TYPED(HashTable)* table, KEY key);

bool TYPED(hasInHashTable)(TYPED(HashTable)* table, KEY key);

void TYPED(deleteFromHashTable)(TYPED(HashTable)* table, KEY key);

