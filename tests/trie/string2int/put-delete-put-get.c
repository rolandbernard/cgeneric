// test:

#include <assert.h>
#include <string.h>

#define TYPED(NAME) NAME ## Test

#define KEY const char*
#define LENGTH(VALUE) (strlen(VALUE))
#define GET_KEY(VALUE, N) ((unsigned char)VALUE[N])

#include "trie/trie.c"

int main() {
    TrieTest map;
    initTrieTest(&map);
    putInTrieTest(&map, "Hello", 1);
    assert(sizeOfTrieTest(&map) == 1);
    putInTrieTest(&map, "World", 2);
    assert(sizeOfTrieTest(&map) == 2);
    putInTrieTest(&map, "Ok", 4);
    assert(sizeOfTrieTest(&map) == 3);
    putInTrieTest(&map, "Test", 4);
    assert(sizeOfTrieTest(&map) == 4);
    deleteFromTrieTest(&map, "Ok");
    assert(sizeOfTrieTest(&map) == 3);
    deleteFromTrieTest(&map, "Test");
    assert(sizeOfTrieTest(&map) == 2);
    putInTrieTest(&map, "Ok", 4);
    assert(sizeOfTrieTest(&map) == 3);
    putInTrieTest(&map, "Test", 4);
    assert(sizeOfTrieTest(&map) == 4);
    assert(getFromTrieTest(&map, "Hello") == 1);
    assert(getFromTrieTest(&map, "World") == 2);
    assert(getFromTrieTest(&map, "Ok") == 4);
    assert(getFromTrieTest(&map, "Test") == 4);
    deinitTrieTest(&map);
    return 0;
}
