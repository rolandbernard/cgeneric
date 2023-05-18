// test:

#include <assert.h>

#define TYPED(NAME) NAME ## Test

#include "hash.c"
#include "hash-table/hash-table.c"

int main() {
    HashTableTest map;
    initHashTableTest(&map);
    for (int i = 0; i < 1000; i++) {
        putInHashTableTest(&map, i, 2*i);
        assert(sizeOfHashTableTest(&map) == (size_t)i + 1);
    }
    HashTableIteratorTest it = getHashTableIteratorTest(&map);
    size_t i = 0;
    while (hasNextHashTableTest(&it)) {
        HashTableEntryTest v = getNextHashTableTest(&it);
        assert(v.value == 2*(int)v.key);
        i++;
    }
    assert(i == 1000);
    deinitHashTableTest(&map);
    return 0;
}

