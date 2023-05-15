// test:

#include <assert.h>

#define TYPED(NAME) NAME ## Test

#include "hash.c"
#include "hamt/hamt.c"

int main() {
    HamtTest map;
    initHamtTest(&map);
    for (int k = 0; k < 1000; k++) {
        for (int i = 0; i < 50; i++) {
            putInHamtTest(&map, 100*k + i, 2*i);
        }
        for (int i = 0; i < 25; i++) {
            deleteFromHamtTest(&map, 100*k + i);
        }
        for (int i = 0; i < 25; i++) {
            putInHamtTest(&map, 100*k + i, 2*i);
        }
        for (int i = 50; i < 100; i++) {
            putInHamtTest(&map, 100*k + i, 2*i);
        }
    }
    assert(sizeOfHamtTest(&map) == 100000);
    for (int i = 0; i < 100000; i++) {
        int val = getOrDefaultFromHamtTest(&map, i, 0);
        assert(val == 2*(i % 100));
    }
    deinitHamtTest(&map);
    return 0;
}
