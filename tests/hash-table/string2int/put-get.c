// test:

#include <assert.h>
#include <string.h>

#include "hash.c"

#define TYPED(NAME) NAME ## Test

#define KEY const char*
#define HASH(KEY) hashString(KEY)
#define EQUALS(FIRST, SECOND) strcmp(FIRST, SECOND) == 0
#define IMPLICIT_STATE

#include "hash-table/hash-table.c"

int main() {
    HashTableTest map;
    initHashTableTest(&map);
    putInHashTableTest(&map, "Hello", 1);
    assert(sizeOfHashTableTest(&map) == 1);
    putInHashTableTest(&map, "World", 2);
    assert(sizeOfHashTableTest(&map) == 2);
    putInHashTableTest(&map, "Ok", 4);
    assert(sizeOfHashTableTest(&map) == 3);
    putInHashTableTest(&map, "Test", 4);
    assert(sizeOfHashTableTest(&map) == 4);
    assert(getFromHashTableTest(&map, "Hello") == 1);
    assert(getFromHashTableTest(&map, "World") == 2);
    assert(getFromHashTableTest(&map, "Ok") == 4);
    assert(getFromHashTableTest(&map, "Test") == 4);
    deinitHashTableTest(&map);
    return 0;
}
