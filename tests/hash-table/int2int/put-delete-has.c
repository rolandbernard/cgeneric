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
        assert(sizeOfHashTableTest(&map) == 1 + (size_t)i);
    }
    for (int i = 0; i < 500; i++) {
        deleteFromHashTableTest(&map, i);
        assert(sizeOfHashTableTest(&map) == 999 - (size_t)i);
    }
    for (int i = 0; i < 500; i++) {
        assert(!hasInHashTableTest(&map, i));
    }
    for (int i = 500; i < 1000; i++) {
        assert(hasInHashTableTest(&map, i));
    }
    deinitHashTableTest(&map);
    return 0;
}
