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
    insertIntoTrieTest(&map, "Hello");
    assert(sizeOfTrieTest(&map) == 1);
    insertIntoTrieTest(&map, "World");
    assert(sizeOfTrieTest(&map) == 2);
    insertIntoTrieTest(&map, "Ok");
    assert(sizeOfTrieTest(&map) == 3);
    insertIntoTrieTest(&map, "Test");
    assert(sizeOfTrieTest(&map) == 4);
    deleteFromTrieTest(&map, "Ok");
    assert(sizeOfTrieTest(&map) == 3);
    deleteFromTrieTest(&map, "Test");
    assert(sizeOfTrieTest(&map) == 2);
    assert(hasInTrieTest(&map, "Hello"));
    assert(hasInTrieTest(&map, "World"));
    assert(!hasInTrieTest(&map, "Ok"));
    assert(!hasInTrieTest(&map, "Test"));
    deinitTrieTest(&map);
    return 0;
}
