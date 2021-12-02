// test:

#include <assert.h>

#define TYPED(NAME) NAME ## Test

#include "trie/trie.c"

int main() {
    TrieTest map;
    initTrieTest(&map);
    assert(sizeOfTrieTest(&map) == 0);
    deinitTrieTest(&map);
    return 0;
}
