// test:

#include <assert.h>

#define TYPED(NAME) NAME ## Test

#include "hash.c"
#include "hash-table/hash-table.c"

int main() {
    HashTableTest map;
    initHashTableTest(&map);
    assert(sizeOfHashTableTest(&map) == 0);
    deinitHashTableTest(&map);
    return 0;
}
