// test:

#include <assert.h>

#define TYPED(NAME) NAME ## Test

#include "hash.c"
#include "hamt/hamt.c"

int main() {
    HamtTest map;
    initHamtTest(&map);
    assert(sizeOfHamtTest(&map) == 0);
    deinitHamtTest(&map);
    deinitHamtTest(&map);
    return 0;
}
