// test:

#include <assert.h>
#include <string.h>

#define TYPED(NAME) NAME ## Test

#define KEY const char*
#define LENGTH(VALUE) (strlen(VALUE))
#define GET_KEY(VALUE, N) ((unsigned char)VALUE[N])
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
