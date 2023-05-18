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
    HamtTest copy;
    copyHamtTest(&copy, &map);
    for (int k = 0; k < 1500; k++) {
        for (int i = 0; i < 50; i++) {
            putInHamtTest(&map, 100*k + i, 4*i);
            int val = getOrDefaultFromHamtTest(&map, 100*k + i, 0);
            assert(val == 4 * i);
        }
        for (int i = 0; i < 25; i++) {
            deleteFromHamtTest(&map, 100*k + i);
        }
        for (int i = 0; i < 25; i++) {
            putInHamtTest(&map, 100*k + i, 4*i);
        }
        for (int i = 50; i < 100; i++) {
            putInHamtTest(&map, 100*k + i, 4*i);
        }
    }
    assert(sizeOfHamtTest(&map) == 150000);
    for (int i = 0; i < 150000; i++) {
        int val = getOrDefaultFromHamtTest(&map, i, 0);
        assert(val == 4*(i % 100));
    }
    assert(sizeOfHamtTest(&copy) == 100000);
    for (int i = 0; i < 100000; i++) {
        int val = getOrDefaultFromHamtTest(&copy, i, 0);
        assert(val == 2*(i % 100));
    }
    HamtTest copy2;
    copyHamtTest(&copy2, &map);
    for (int i = 100000; i < 200000; i++) {
        deleteFromHamtTest(&map, i);
    }
    for (int k = 0; k < 1000; k++) {
        for (int i = 0; i < 50; i++) {
            putInHamtTest(&map, 100*k + i, 8*i);
            int val = getOrDefaultFromHamtTest(&map, 100*k + i, 0);
            assert(val == 8 * i);
        }
        for (int i = 0; i < 25; i++) {
            deleteFromHamtTest(&map, 100*k + i);
        }
        for (int i = 0; i < 25; i++) {
            putInHamtTest(&map, 100*k + i, 8*i);
        }
        for (int i = 50; i < 100; i++) {
            putInHamtTest(&map, 100*k + i, 8*i);
        }
    }
    HamtIteratorTest it3 = getHamtIteratorTest(&map);
    size_t i3 = 0;
    while (hasNextHamtTest(&it3)) {
        HamtEntryTest v = getNextHamtTest(&it3);
        assert(v.value == 8*(v.key % 100));
        i3++;
    }
    assert(i3 == 100000);
    deinitHamtTest(&map);
    HamtIteratorTest it2 = getHamtIteratorTest(&copy2);
    size_t i2 = 0;
    while (hasNextHamtTest(&it2)) {
        HamtEntryTest v = getNextHamtTest(&it2);
        assert(v.value == 4*(v.key % 100));
        i2++;
    }
    assert(i2 == 150000);
    deinitHamtTest(&copy2);
    HamtIteratorTest it = getHamtIteratorTest(&copy);
    size_t i = 0;
    while (hasNextHamtTest(&it)) {
        HamtEntryTest v = getNextHamtTest(&it);
        assert(v.value == 2*(v.key % 100));
        i++;
    }
    assert(i == 100000);
    deinitHamtTest(&copy);
    return 0;
}

