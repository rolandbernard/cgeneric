
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "default.h"

typedef struct TYPED(Hamt) TYPED(Hamt);

typedef struct TYPED(HamtNode) TYPED(HamtNode);

struct TYPED(HamtNode) {
    size_t refs;
    uint32_t keymap;
    uint32_t treemap;
    char data[0];
};

struct TYPED(Hamt) {
    TYPED(HamtNode)* root;
};

void TYPED(initHamt)(TYPED(Hamt)* table);

void TYPED(deinitHamt)(TYPED(Hamt)* table);

void TYPED(copyHamt)(TYPED(Hamt)* destination, TYPED(Hamt)* source);

size_t TYPED(sizeOfHamt)(TYPED(Hamt)* table);

bool TYPED(putInHamt)(TYPED(Hamt)* table, KEY key, VALUE value);

bool TYPED(getFromHamt)(TYPED(Hamt)* table, KEY key, VALUE* value);

bool TYPED(deleteFromHamt)(TYPED(Hamt)* table, KEY key);

typedef struct TYPED(HamtIterator) TYPED(HamtIterator);

typedef struct TYPED(HamtEntry) TYPED(HamtEntry);

struct TYPED(HamtIterator) {
    TYPED(HamtNode)* path[16];
    size_t offset;
    size_t depth;
};

struct TYPED(HamtEntry) {
    KEY key;
    VALUE value;
};

TYPED(HamtIterator) TYPED(getHamtIterator)(TYPED(Hamt)* table);

bool TYPED(hasNextHamt)(TYPED(HamtIterator)* iter);

TYPED(HamtEntry) TYPED(getNextHamt)(TYPED(HamtIterator)* iter);
