// test:

#include <assert.h>

#define TYPED(NAME) NAME ## Test

#include "hash.c"
#include "hamt/hamt.c"

int main() {
    HamtTest map;
    initHamtTest(&map);
    for (int i = 0; i < 1000; i++) {
        putInHamtTest(&map, i, 2*i);
        assert(sizeOfHamtTest(&map) == 1 + (size_t)i);
    }
    for (int i = 0; i < 500; i++) {
        deleteFromHamtTest(&map, i);
        assert(sizeOfHamtTest(&map) == 999 - (size_t)i);
    }
    for (int i = 0; i < 500; i++) {
        assert(!hasInHamtTest(&map, i));
    }
    for (int i = 500; i < 1000; i++) {
        assert(hasInHamtTest(&map, i));
    }
    deinitHamtTest(&map);
    return 0;
}
