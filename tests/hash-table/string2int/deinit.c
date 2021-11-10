// test:

#include <assert.h>
#include <string.h>

#include "hash.c"

#define TYPED(NAME) NAME ## Test

#define KEY const char*
#define HASH(KEY) hashString(KEY)
#define EQUALS(FIRST, SECOND) (strcmp(FIRST, SECOND) == 0)
#define IMPLICIT_STATE

#include "hash-table/hash-table.c"

int main() {
    HashTableTest map;
    initHashTableTest(&map);
    assert(sizeOfHashTableTest(&map) == 0);
    deinitHashTableTest(&map);
    deinitHashTableTest(&map);
    return 0;
}
