// test:

#include <assert.h>
#include <string.h>

#include "hash.c"

#define TYPED(NAME) NAME ## Test

#define KEY const char*
#define HASH(KEY) hashString(KEY)
#define EQUALS(FIRST, SECOND) (strcmp(FIRST, SECOND) == 0)
#define IMPLICIT_STATE

#include "hamt/hamt.c"

int main() {
    HamtTest map;
    initHamtTest(&map);
    assert(sizeOfHamtTest(&map) == 0);
    deinitHamtTest(&map);
    deinitHamtTest(&map);
    return 0;
}
