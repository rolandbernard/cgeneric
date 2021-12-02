// test:

#include <assert.h>

#define TYPED(NAME) NAME ## Test

#include "trie/trie.c"

int main() {
    TrieTest map;
    initTrieTest(&map);
    for (int i = 0; i < 1000; i++) {
        putInTrieTest(&map, i, 2*i);
        if (i % 100 == 0) {
            assert(sizeOfTrieTest(&map) == (size_t)i + 1);
        }
    }
    for (int i = 0; i < 1000; i++) {
        int val = getFromTrieTest(&map, i);
        assert(val == 2*i);
    }
    deinitTrieTest(&map);
    return 0;
}
