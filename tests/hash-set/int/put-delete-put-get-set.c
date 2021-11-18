// test:

#include <assert.h>

#define TYPED(NAME) NAME ## Test

#include "hash.c"
#include "hash-set/hash-set.c"

int main() {
    HashSetTest map;
    initHashSetTest(&map);
    for (int i = 0; i < 1000; i++) {
        insertIntoHashSetTest(&map, i*i);
        assert(sizeOfHashSetTest(&map) == 1 + (size_t)i);
    }
    for (int i = 0; i < 1000; i++) {
        insertIntoHashSetTest(&map, i*i);
        assert(sizeOfHashSetTest(&map) == 1000);
    }
    for (int i = 0; i < 500; i++) {
        deleteFromHashSetTest(&map, i*i);
        assert(sizeOfHashSetTest(&map) == 999 - (size_t)i);
    }
    for (int i = 0; i < 500; i++) {
        deleteFromHashSetTest(&map, i*i);
        assert(sizeOfHashSetTest(&map) == 500);
    }
    for (int i = 0; i < 500; i++) {
        insertIntoHashSetTest(&map, i*i);
        assert(sizeOfHashSetTest(&map) == 501 + (size_t)i);
    }
    for (int i = 0; i < 500; i++) {
        insertIntoHashSetTest(&map, i*i);
        assert(sizeOfHashSetTest(&map) == 1000);
    }
    for (int i = 0; i < 1000; i++) {
        assert(hasInHashSetTest(&map, i*i));
    }
    deinitHashSetTest(&map);
    return 0;
}
