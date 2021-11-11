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
    assert(sizeOfHashSetTest(&map) == 0);
    deinitHashSetTest(&map);
    return 0;
}
