// test:

#include <assert.h>

#define TYPED(NAME) NAME ## Test
#define IS_SET

#include "trie/trie.c"

int main() {
    TrieTest map;
    initTrieTest(&map);
    assert(sizeOfTrieTest(&map) == 0);
    deinitTrieTest(&map);
    deinitTrieTest(&map);
    return 0;
}
