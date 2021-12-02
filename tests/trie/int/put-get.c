// test:

#include <assert.h>

#define TYPED(NAME) NAME ## Test
#define IS_SET

#include "trie/trie.c"

int main() {
    TrieTest map;
    initTrieTest(&map);
    for (int i = 0; i < 1000; i++) {
        insertIntoTrieTest(&map, i*i);
        if (i % 100 == 0) {
            assert(sizeOfTrieTest(&map) == (size_t)i + 1);
        }
    }
    for (int i = 0; i < 1000; i++) {
        assert(hasInTrieTest(&map, i*i));
    }
    deinitTrieTest(&map);
    return 0;
}
