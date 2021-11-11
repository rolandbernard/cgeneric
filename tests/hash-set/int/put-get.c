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
        assert(sizeOfHashSetTest(&map) == (size_t)i + 1);
    }
    for (int i = 0; i < 1000; i++) {
        assert(hasInHashSetTest(&map, i*i));
    }
    deinitHashSetTest(&map);
    return 0;
}
