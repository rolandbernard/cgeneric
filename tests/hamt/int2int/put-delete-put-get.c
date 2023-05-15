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
        putInHamtTest(&map, i, 2*i);
        assert(sizeOfHamtTest(&map) == 501 + (size_t)i);
    }
    for (int i = 0; i < 1000; i++) {
        int val = getOrDefaultFromHamtTest(&map, i, 0);
        assert(val == 2*i);
    }
    deinitHamtTest(&map);
    return 0;
}
