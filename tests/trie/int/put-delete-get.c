// test:

#include <assert.h>

#define KEY unsigned long
#define TYPED(NAME) NAME ## Test
#define IS_SET

#include "trie/trie.c"

int main() {
    TrieTest map;
    initTrieTest(&map);
    for (KEY i = 0; i < 1000; i++) {
        insertIntoTrieTest(&map, i*i*i*i);
        if (i % 100 == 0) {
            assert(sizeOfTrieTest(&map) == (size_t)i + 1);
        }
    }
    for (KEY i = 0; i < 500; i++) {
        deleteFromTrieTest(&map, i*i*i*i);
        if (i % 100 == 0) {
            assert(sizeOfTrieTest(&map) == 999 - (size_t)i);
        }
    }
    for (KEY i = 500; i < 1000; i++) {
        assert(hasInTrieTest(&map, i*i*i*i));
    }
    deinitTrieTest(&map);
    return 0;
}
