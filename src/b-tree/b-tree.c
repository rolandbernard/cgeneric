
#include <assert.h>
#include <stddef.h>

#include "b-tree.h"

void TYPED(initBTree)(TYPED(BTree)* tree) {
    tree->root = NULL;
}

static void TYPED(freeBTreeNodes)(TYPED(BTreeNode)* node) {
    if (node != NULL) {
        for (size_t i = 0; i < node->count; i++) {
            TYPED(freeBTreeNodes)(node->child[i]);
        }
        FREE(node);
    }
}

void TYPED(deinitBTree)(TYPED(BTree)* tree) {
    TYPED(freeBTreeNodes)(tree->root);
    tree->root = NULL;
}

static size_t TYPED(countBTreeNodes)(TYPED(BTreeNode)* node) {
    if (node != NULL) {
        size_t ret = 1;
        for (size_t i = 0; i < node->count; i++) {
            ret += TYPED(countBTreeNodes)(node->child[i]);
        }
        return ret;
    } else {
        return 0;
    }
}

size_t TYPED(sizeOfBTree)(TYPED(BTree)* tree) {
    return TYPED(countBTreeNodes)(tree->root);
}

TYPE TYPED(firstBTree)(TYPED(BTree)* tree) {
    TYPED(BTreeNode)* c = tree->root;
    while (c->child[0] != NULL) {
        c = c->child[0];
    }
    return c->values[0];
}

TYPE TYPED(lastBTree)(TYPED(BTree)* tree) {
    TYPED(BTreeNode)* c = tree->root;
    while (c->child[c->count - 1] != NULL) {
        c = c->child[c->count - 1];
    }
    return c->values[c->count];
}

static size_t TYPED(lowerBound)(TYPE* array, size_t size, TYPE value) {
    size_t i = 0;
    size_t j = size;
    while (i != j) {
        size_t h = (i + j) / 2;
        if (!LESS_THAN(array[h], value)) {
            j = h;
        } else {
            i = h + 1;
        }
    }
    return i;
}

bool TYPED(hasInBTree)(TYPED(BTree)* tree, TYPE element) {
    TYPED(BTreeNode)* c = tree->root;
    while (c != NULL) {
        size_t d = TYPED(lowerBound)(c->values, c->count, element);
        if (
            d < c->count && !LESS_THAN(c->values[d], element) && !LESS_THAN(element, c->values[d])
        ) {
            return true;
        }
        c = c->child[d];
    }
    return false;
}

void TYPED(insertIntoBTree)(TYPED(BTree)* tree, TYPE element);

void TYPED(deleteFromBTree)(TYPED(BTree)* tree, TYPE element);

TYPED(BTreeIterator) TYPED(getBTreeIterator)(TYPED(BTree)* tree) {
    TYPED(BTreeNode)* c = tree->root;
    while (c->child[0] != NULL) {
        c = c->child[0];
    }
    TYPED(BTreeIterator) ret = {
        .current = c,
        .n = 0,
    };
    return ret;
}

bool TYPED(hasNextBTree)(TYPED(BTreeIterator)* iter) {
    return iter->current != NULL;
}

static size_t TYPED(positionOfChild)(TYPED(BTreeNode)* parent, TYPED(BTreeNode)* child) {
    size_t i = 0;
    while (i <= parent->count && parent->child[i] != child) {
        i++;
    }
    return i;
}

TYPE TYPED(getNextBTree)(TYPED(BTreeIterator)* iter) {
    TYPE ret = iter->current->values[iter->n];
    iter->n++;
    if (iter->current->child[iter->n] != NULL) {
        TYPED(BTreeNode)* c = iter->current->child[iter->n];
        while (c->child[0] != NULL) {
            c = c->child[0];
        }
        iter->current = c;
    } else {
        TYPED(BTreeNode)* parent = iter->current->parent;
        iter->n = TYPED(positionOfChild)(parent, iter->current);
        while (parent != NULL && iter->n == parent->count) {
            iter->current = parent;
            parent = iter->current->parent;
            iter->n = TYPED(positionOfChild)(parent, iter->current);
        }
        iter->current = parent;
    }
    return ret;
}

