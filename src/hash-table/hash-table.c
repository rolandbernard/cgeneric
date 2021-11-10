
#include "hash-table.h"

#ifndef IMPLICIT_STATE
#define EMPTY 0
#define DELETED 1
#define VALID 2
#endif

static bool TYPED(isIndexValid)(TYPED(HashTable)* table, size_t idx) {
#ifdef IMPLICIT_STATE
    return IS_VALID(table->keys[idx], table->values[idx]);
#else
    return table->state[idx] == VALID;
#endif
}

static bool TYPED(continueSearch)(TYPED(HashTable)* table, size_t idx, KEY key) {
#ifdef IMPLICIT_STATE
    return IS_DELETED(table->keys[idx], table->values[idx])
           || (IS_VALID(table->keys[idx], table->values[idx]) && !EQUALS(table->keys[idx], key));
#else
    return table->state[idx] == DELETED
           || (table->state[idx] == VALID && !EQUALS(table->keys[idx], key));
#endif
}

static size_t TYPED(findIndexHashTable)(TYPED(HashTable)* table, KEY key) {
    size_t idx = HASH(key) % table->capacity;
    while (TYPED(continueSearch)(table, idx, key)) {
        idx = (idx + 1) % table->capacity;
    }
    return idx;
}

static bool TYPED(continueInsertSearch)(TYPED(HashTable)* table, size_t idx, KEY key) {
#ifdef IMPLICIT_STATE
    return IS_VALID(table->keys[idx], table->values[idx]) && !EQUALS(table->keys[idx], key);
#else
    return table->state[idx] == VALID && !EQUALS(table->keys[idx], key);
#endif
}

static size_t TYPED(insertIndexHashTable)(TYPED(HashTable)* table, KEY key) {
    size_t idx = HASH(key) % table->capacity;
    while (TYPED(continueInsertSearch)(table, idx, key)) {
        idx = (idx + 1) % table->capacity;
    }
    return idx;
}

static void TYPED(rebuildHashTable)(TYPED(HashTable)* table, size_t size) {
    TYPED(HashTable) new;
    new.capacity = size;
    new.count = 0;
    new.keys = ALLOC(KEY, size);
    new.values = ALLOC(VALUE, size);
#ifdef IMPLICIT_STATE
    for (size_t i = 0; i < size; i++) {
        SET_EMPTY(new.keys[i], new.values[i]);
    }
#else
    new.state = ZALLOC(char, size);
#endif
    for (size_t i = 0; i < table->capacity; i++) {
        if (TYPED(isIndexValid)(table, i)) {
            size_t idx = TYPED(insertIndexHashTable)(&new, table->keys[i]);
            new.keys[idx] = table->keys[i];
            new.values[idx] = table->values[i];
#ifndef IMPLICIT_STATE
            new.state[idx] = VALID;
#endif
        }
    }
    FREE(table->keys);
    table->keys = new.keys;
    FREE(table->values);
    table->values = new.values;
#ifndef IMPLICIT_STATE
    FREE(table->state);
    table->state = new.state;
#endif
    table->capacity = new.capacity;
}

static void TYPED(tryResizingHashTable)(TYPED(HashTable)* table) {
    if (table->count == table->capacity || SHOULD_GROW(table->count, table->capacity)) {
        TYPED(rebuildHashTable)(table, GROWTH_FUNCTION(table->capacity));
    } else if (SHOULD_SHRINK(table->count, table->capacity)) {
        TYPED(rebuildHashTable)(table, SHRINK_FUNCTION(table->capacity));
    }
}

void TYPED(initHashTable)(TYPED(HashTable)* table) {
    table->capacity = 0;
    table->count = 0;
    table->keys = NULL;
    table->values = NULL;
#ifndef IMPLICIT_STATE
    table->state = NULL;
#endif
}

void TYPED(deinitHashTable)(TYPED(HashTable)* table) {
    FREE(table->keys);
    FREE(table->values);
#ifndef IMPLICIT_STATE
    FREE(table->state);
#endif
    TYPED(initHashTable)(table);
}

size_t TYPED(sizeOfHashTable)(TYPED(HashTable)* table) {
    return table->count;
}

void TYPED(reserveHashTable)(TYPED(HashTable)* table, size_t size) {
    if (table->capacity < size) {
        TYPED(rebuildHashTable)(table, size);
    }
}

void TYPED(putInHashTable)(TYPED(HashTable)* table, KEY key, VALUE value) {
    TYPED(tryResizingHashTable)(table);
    size_t idx = TYPED(findIndexHashTable)(table, key);
    if (TYPED(isIndexValid)(table, idx)) {
        table->values[idx] = value;
    } else {
        idx = TYPED(insertIndexHashTable)(table, key);
        table->keys[idx] = key;
        table->values[idx] = value;
#ifndef IMPLICIT_STATE
        table->state[idx] = VALID;
#endif
        table->count++;
    }
}

VALUE TYPED(getFromHashTable)(TYPED(HashTable)* table, KEY key) {
    if (table->count != 0) {
        size_t idx = TYPED(findIndexHashTable)(table, key);
        if (TYPED(isIndexValid)(table, idx)) {
            return table->values[idx];
        }
    }
    VALUE ret = DEFAULT;
    return ret;
}

bool TYPED(hasInHashTable)(TYPED(HashTable)* table, KEY key) {
    if (table->count != 0) {
        size_t idx = TYPED(findIndexHashTable)(table, key);
        if (TYPED(isIndexValid)(table, idx)) {
            return true;
        }
    }
    return false;
}

void TYPED(deleteFromHashTable)(TYPED(HashTable)* table, KEY key) {
    if (table->count != 0) {
        size_t idx = TYPED(findIndexHashTable)(table, key);
        if (TYPED(isIndexValid)(table, idx)) {
#ifdef IMPLICIT_STATE
            SET_DELETED(table->keys[idx], table->values[idx]);
#else
            table->state[idx] = DELETED;
#endif
            table->count--;
            TYPED(tryResizingHashTable)(table);
        }
    }
}

#undef EMPTY
#undef DELETED
#undef VALID

