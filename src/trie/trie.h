
#include <stddef.h>
#include <stdbool.h>

#include "default.h"

typedef struct TYPED(Trie) TYPED(Trie);

typedef struct TYPED(TrieNode) TYPED(TrieNode);

struct TYPED(TrieNode) {
    TYPED(TrieNode)* child[KEY_SIZE];
#ifndef IS_SET
    VALUE value;
#ifndef IMPLICIT_STATE
    bool valid;
#endif
#else
    bool valid;
#endif
};

struct TYPED(Trie) {
    TYPED(TrieNode)* root;
};

void TYPED(initTrie)(TYPED(Trie)* trie);

void TYPED(deinitTrie)(TYPED(Trie)* trie);

size_t TYPED(sizeOfTrie)(TYPED(Trie)* trie);

#ifndef IS_SET
void TYPED(putInTrie)(TYPED(Trie)* trie, KEY key, VALUE value);

VALUE TYPED(getFromTrie)(TYPED(Trie)* trie, KEY key);
#else
void TYPED(insertIntoTrie)(TYPED(Trie)* trie, KEY key);
#endif

bool TYPED(hasInTrie)(TYPED(Trie)* trie, KEY key);

void TYPED(deleteFromTrie)(TYPED(Trie)* trie, KEY key);

