// test:

#include <assert.h>

#define TYPED(NAME) NAME ## Test

#include "hash.c"
#include "hash-set/hash-set.c"

int main() {
    HashSetTest map;
    initHashSetTest(&map);
    assert(sizeOfHashSetTest(&map) == 0);
    deinitHashSetTest(&map);
    deinitHashSetTest(&map);
    return 0;
}
