
#include "trie.h"

void TYPED(initTrie)(TYPED(Trie)* trie) {
    trie->root = NULL;
}

static void TYPED(freeTrieNodes)(TYPED(TrieNode)* node) {
    if (node != NULL) {
        for (size_t i = 0; i < KEY_SIZE; i++) {
            TYPED(freeTrieNodes)(node->child[i]);
        }
        FREE(node);
    }
}

void TYPED(deinitTrie)(TYPED(Trie)* trie) {
    TYPED(freeTrieNodes)(trie->root);
    trie->root = NULL;
}

static size_t TYPED(countTrieNodes)(TYPED(TrieNode)* node) {
    if (node != NULL) {
        int ret = 0;
#ifndef IMPLICIT_STATE
        if (node->valid) {
#else
        if (IS_VALID(node->value)) {
#endif
            ret++;
        }
        for (size_t i = 0; i < KEY_SIZE; i++) {
            ret += TYPED(countTrieNodes)(node->child[i]);
        }
        return ret;
    } else {
        return 0;
    }
}

size_t TYPED(sizeOfTrie)(TYPED(Trie)* trie) {
    return TYPED(countTrieNodes)(trie->root);
}

bool TYPED(hasInTrie)(TYPED(Trie)* trie, KEY key) {
    size_t len = LENGTH(key);
    TYPED(TrieNode)* c = trie->root;
    for (size_t i = 0; c != NULL && i < len; i++) {
        c = c->child[GET_KEY(key, i)];
    }
#ifndef IMPLICIT_STATE
    if (c != NULL && c->valid) {
#else
    if (c != NULL && IS_VALID(c->value)) {
#endif
        return true;
    } else {
        return false;
    }
}

#ifndef IS_SET
void TYPED(putInTrie)(TYPED(Trie)* trie, KEY key, VALUE value) {
    size_t len = LENGTH(key);
    TYPED(TrieNode)** c = &trie->root;
    for (size_t i = 0; i < len; i++) {
        if (*c == NULL) {
            *c = ZALLOC(TYPED(TrieNode), 1);
        }
        c = &(*c)->child[GET_KEY(key, i)];
    }
    if (*c == NULL) {
        *c = ZALLOC(TYPED(TrieNode), 1);
    }
#ifndef IMPLICIT_STATE
    (*c)->valid = true;
#endif
    (*c)->value = value;
}

VALUE TYPED(getFromTrie)(TYPED(Trie)* trie, KEY key) {
    size_t len = LENGTH(key);
    TYPED(TrieNode)* c = trie->root;
    for (size_t i = 0; c != NULL && i < len; i++) {
        c = c->child[GET_KEY(key, i)];
    }
#ifndef IMPLICIT_STATE
    if (c != NULL && c->valid) {
#else
    if (c != NULL && IS_VALID(c->value)) {
#endif
        return c->value;
    } else {
        return DEFAULT;
    }
}
#else
void TYPED(insertIntoTrie)(TYPED(Trie)* trie, KEY key) {
    size_t len = LENGTH(key);
    TYPED(TrieNode)** c = &trie->root;
    for (size_t i = 0; i < len; i++) {
        if (*c == NULL) {
            *c = ZALLOC(TYPED(TrieNode), 1);
        }
        c = &(*c)->child[GET_KEY(key, i)];
    }
    if (*c == NULL) {
        *c = ZALLOC(TYPED(TrieNode), 1);
    }
    (*c)->valid = true;
}
#endif

void TYPED(deleteFromTrie)(TYPED(Trie)* trie, KEY key) {
    size_t len = LENGTH(key);
    size_t index[len];
    TYPED(TrieNode)* nodes[len + 1];
    TYPED(TrieNode)* c = trie->root;
    for (size_t i = 0; c != NULL && i < len; i++) {
        nodes[i] = c;
        index[i] = GET_KEY(key, i);
        c = c->child[index[i]];
    }
    nodes[len] = c;
    if (c != NULL) {
#ifndef IMPLICIT_STATE
        c->valid = false;
#else
        SET_INVALID(c->value);
#endif
        for (size_t i = len + 1; i > 0;) {
            i--;
#ifndef IMPLICIT_STATE
            if (nodes[i]->valid) {
#else
            if (IS_VALID(nodes[i]->value)) {
#endif
                break;
            }
            for (size_t j = 0; j < KEY_SIZE; j++) {
                if (nodes[i]->child[j] != NULL) {
                    return;
                }
            }
            if (i == 0) {
                trie->root = NULL;
            } else {
                nodes[i - 1]->child[index[i - 1]] = NULL;
            }
            FREE(nodes[i]);
        }
    }
}

