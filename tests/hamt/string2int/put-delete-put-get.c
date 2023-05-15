// test:

#include <assert.h>
#include <string.h>

#include "hash.c"

#define TYPED(NAME) NAME ## Test

#define KEY const char*
#define HASH(KEY) hashString(KEY)
#define EQUALS(FIRST, SECOND) strcmp(FIRST, SECOND) == 0
#define IMPLICIT_STATE

#include "hamt/hamt.c"

int main() {
    HamtTest map;
    initHamtTest(&map);
    putInHamtTest(&map, "Hello", 1);
    assert(sizeOfHamtTest(&map) == 1);
    putInHamtTest(&map, "World", 2);
    assert(sizeOfHamtTest(&map) == 2);
    putInHamtTest(&map, "Ok", 4);
    assert(sizeOfHamtTest(&map) == 3);
    putInHamtTest(&map, "Test", 4);
    assert(sizeOfHamtTest(&map) == 4);
    deleteFromHamtTest(&map, "Ok");
    assert(sizeOfHamtTest(&map) == 3);
    deleteFromHamtTest(&map, "Test");
    assert(sizeOfHamtTest(&map) == 2);
    putInHamtTest(&map, "Ok", 4);
    assert(sizeOfHamtTest(&map) == 3);
    putInHamtTest(&map, "Test", 4);
    assert(sizeOfHamtTest(&map) == 4);
    assert(getOrDefaultFromHamtTest(&map, "Hello", 0) == 1);
    assert(getOrDefaultFromHamtTest(&map, "World", 0) == 2);
    assert(getOrDefaultFromHamtTest(&map, "Ok", 0) == 4);
    assert(getOrDefaultFromHamtTest(&map, "Test", 0) == 4);
    deinitHamtTest(&map);
    return 0;
}
