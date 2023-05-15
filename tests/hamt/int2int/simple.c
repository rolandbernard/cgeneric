// test:

#include <assert.h>

#define TYPED(NAME) NAME ## Test

#include "hash.c"
#include "hamt/hamt.c"

int main() {
    HamtTest map;
    initHamtTest(&map);
    for (int i = 0; i < 11; i++) {
        putInHamtTest(&map, i, 2*i);
        assert(sizeOfHamtTest(&map) == (size_t)i + 1);
    }
    for (int i = 0; i < 11; i++) {
        int val = getOrDefaultFromHamtTest(&map, i, 0);
        assert(val == 2*i);
    }
    deinitHamtTest(&map);
    return 0;
}
