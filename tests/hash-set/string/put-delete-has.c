// test:

#include <assert.h>
#include <string.h>

#include "hash.c"

#define TYPED(NAME) NAME ## Test

#define TYPE const char*
#define HASH(KEY) hashString(KEY)
#define EQUALS(FIRST, SECOND) strcmp(FIRST, SECOND) == 0
#define IMPLICIT_STATE

#include "hash-set/hash-set.c"

int main() {
    HashSetTest map;
    initHashSetTest(&map);
    insertIntoHashSetTest(&map, "Hello");
    assert(sizeOfHashSetTest(&map) == 1);
    insertIntoHashSetTest(&map, "World");
    assert(sizeOfHashSetTest(&map) == 2);
    insertIntoHashSetTest(&map, "Ok");
    assert(sizeOfHashSetTest(&map) == 3);
    insertIntoHashSetTest(&map, "Test");
    assert(sizeOfHashSetTest(&map) == 4);
    deleteFromHashSetTest(&map, "Ok");
    assert(sizeOfHashSetTest(&map) == 3);
    deleteFromHashSetTest(&map, "Test");
    assert(sizeOfHashSetTest(&map) == 2);
    assert(hasInHashSetTest(&map, "Hello"));
    assert(hasInHashSetTest(&map, "World"));
    assert(!hasInHashSetTest(&map, "Ok"));
    assert(!hasInHashSetTest(&map, "Test"));
    deinitHashSetTest(&map);
    return 0;
}
