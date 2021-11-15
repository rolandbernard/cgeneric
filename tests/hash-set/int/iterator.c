// test:

#include <assert.h>

#define TYPED(NAME) NAME ## Test

#include "hash.c"
#include "hash-set/hash-set.c"

int main() {
    HashSetTest map;
    initHashSetTest(&map);
    for (int i = 0; i < 1000; i++) {
        insertIntoHashSetTest(&map, 2*i);
        assert(sizeOfHashSetTest(&map) == (size_t)i + 1);
    }
    HashSetIteratorTest it = getHashSetIteratorTest(&map);
    size_t i = 0;
    while (hasNextHashSetTest(&it)) {
        int v = getNextHashSetTest(&it);
        assert(v >= 0 && v <= 2*999 && v % 2 == 0);
        i++;
    }
    assert(i == 1000);
    deinitHashSetTest(&map);
    return 0;
}

