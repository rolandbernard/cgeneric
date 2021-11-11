
#include "hash-set.h"

#ifndef IMPLICIT_STATE
#define EMPTY 0
#define DELETED 1
#define VALID 2
#endif

static bool TYPED(isIndexValid)(TYPED(HashSet)* set, size_t idx) {
#ifdef IMPLICIT_STATE
    return IS_VALID(set->keys[idx]);
#else
    return set->state[idx] == VALID;
#endif
}

static bool TYPED(continueSearch)(TYPED(HashSet)* set, size_t idx, TYPE key) {
#ifdef IMPLICIT_STATE
    return IS_DELETED(set->keys[idx]) || (IS_VALID(set->keys[idx]) && !EQUALS(set->keys[idx], key));
#else
    return set->state[idx] == DELETED
           || (set->state[idx] == VALID && !EQUALS(set->keys[idx], key));
#endif
}

static size_t TYPED(findIndexHashSet)(TYPED(HashSet)* set, TYPE key) {
    size_t idx = HASH(key) % set->capacity;
    while (TYPED(continueSearch)(set, idx, key)) {
        idx = (idx + 1) % set->capacity;
    }
    return idx;
}

static bool TYPED(continueInsertSearch)(TYPED(HashSet)* set, size_t idx, TYPE key) {
#ifdef IMPLICIT_STATE
    return IS_VALID(set->keys[idx]) && !EQUALS(set->keys[idx], key);
#else
    return set->state[idx] == VALID && !EQUALS(set->keys[idx], key);
#endif
}

static size_t TYPED(insertIndexHashSet)(TYPED(HashSet)* set, TYPE key) {
    size_t idx = HASH(key) % set->capacity;
    while (TYPED(continueInsertSearch)(set, idx, key)) {
        idx = (idx + 1) % set->capacity;
    }
    return idx;
}

static void TYPED(rebuildHashSet)(TYPED(HashSet)* set, size_t size) {
    TYPED(HashSet) new;
    new.capacity = size;
    new.count = 0;
    new.keys = ALLOC(TYPE, size);
#ifdef IMPLICIT_STATE
    for (size_t i = 0; i < size; i++) {
        SET_EMPTY(new.keys[i]);
    }
#else
    new.state = ZALLOC(char, size);
#endif
    for (size_t i = 0; i < set->capacity; i++) {
        if (TYPED(isIndexValid)(set, i)) {
            size_t idx = TYPED(insertIndexHashSet)(&new, set->keys[i]);
            new.keys[idx] = set->keys[i];
#ifndef IMPLICIT_STATE
            new.state[idx] = VALID;
#endif
        }
    }
    FREE(set->keys);
    set->keys = new.keys;
#ifndef IMPLICIT_STATE
    FREE(set->state);
    set->state = new.state;
#endif
    set->capacity = new.capacity;
}

static void TYPED(tryResizingHashSet)(TYPED(HashSet)* set) {
    if (set->count == set->capacity || SHOULD_GROW(set->count, set->capacity)) {
        TYPED(rebuildHashSet)(set, GROWTH_FUNCTION(set->capacity));
    } else if (SHOULD_SHRINK(set->count, set->capacity)) {
        TYPED(rebuildHashSet)(set, SHRINK_FUNCTION(set->capacity));
    }
}

void TYPED(initHashSet)(TYPED(HashSet)* set) {
    set->capacity = 0;
    set->count = 0;
    set->keys = NULL;
#ifndef IMPLICIT_STATE
    set->state = NULL;
#endif
}

void TYPED(deinitHashSet)(TYPED(HashSet)* set) {
    FREE(set->keys);
#ifndef IMPLICIT_STATE
    FREE(set->state);
#endif
    TYPED(initHashSet)(set);
}

size_t TYPED(sizeOfHashSet)(TYPED(HashSet)* set) {
    return set->count;
}

void TYPED(reserveHashSet)(TYPED(HashSet)* set, size_t size) {
    if (set->capacity < size) {
        TYPED(rebuildHashSet)(set, size);
    }
}

void TYPED(insertIntoHashSet)(TYPED(HashSet)* set, TYPE key) {
    TYPED(tryResizingHashSet)(set);
    size_t idx = TYPED(findIndexHashSet)(set, key);
    if (!TYPED(isIndexValid)(set, idx)) {
        idx = TYPED(insertIndexHashSet)(set, key);
        set->keys[idx] = key;
#ifndef IMPLICIT_STATE
        set->state[idx] = VALID;
#endif
        set->count++;
    }
}

bool TYPED(hasInHashSet)(TYPED(HashSet)* set, TYPE key) {
    if (set->count != 0) {
        size_t idx = TYPED(findIndexHashSet)(set, key);
        if (TYPED(isIndexValid)(set, idx)) {
            return true;
        }
    }
    return false;
}

void TYPED(deleteFromHashSet)(TYPED(HashSet)* set, TYPE key) {
    if (set->count != 0) {
        size_t idx = TYPED(findIndexHashSet)(set, key);
        if (TYPED(isIndexValid)(set, idx)) {
#ifdef IMPLICIT_STATE
            SET_DELETED(set->keys[idx]);
#else
            set->state[idx] = DELETED;
#endif
            set->count--;
            TYPED(tryResizingHashSet)(set);
        }
    }
}

#undef EMPTY
#undef DELETED
#undef VALID

