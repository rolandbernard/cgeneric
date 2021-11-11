// test:

#include <assert.h>

#define TYPE unsigned long
#define TYPED(NAME) NAME ## Test

#include "hash.c"
#include "hash-set/hash-set.c"

int main() {
    HashSetTest map;
    initHashSetTest(&map);
    for (TYPE i = 0; i < 1000; i++) {
        insertIntoHashSetTest(&map, i*i*i*i);
        assert(sizeOfHashSetTest(&map) == (size_t)i + 1);
    }
    for (TYPE i = 0; i < 500; i++) {
        deleteFromHashSetTest(&map, i*i*i*i);
        assert(sizeOfHashSetTest(&map) == 999 - (size_t)i);
    }
    for (TYPE i = 500; i < 1000; i++) {
        assert(hasInHashSetTest(&map, i*i*i*i));
    }
    deinitHashSetTest(&map);
    return 0;
}
