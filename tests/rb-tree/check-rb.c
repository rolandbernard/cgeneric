
#include <assert.h>
#include <stddef.h>

#ifndef TYPE
#include "rb-tree/rb-tree.h"
#endif

#define LEFT  0
#define RIGHT 1

#define BLACK false
#define RED   true

void assertBlackNodes(TYPED(RBTreeNode)* node, size_t c) {
    if (node == NULL) {
        assert(c == 0);
    } else {
        if (node->color == BLACK) {
            c--;
        }
        assertBlackNodes(node->child[LEFT], c);
        assertBlackNodes(node->child[RIGHT], c);
    }
}

void noRedRed(TYPED(RBTreeNode)* node) {
    if (node != NULL) {
        if (node->color == RED) {
            assert(node->child[LEFT] == NULL || node->child[LEFT]->color == BLACK);
            assert(node->child[RIGHT] == NULL || node->child[RIGHT]->color == BLACK);
        }
        noRedRed(node->child[LEFT]);
        noRedRed(node->child[RIGHT]);
    }
}

void isRBTree(TYPED(RBTree)* tree) {
    noRedRed(tree->root);
    size_t d = 0;
    TYPED(RBTreeNode)* c = tree->root;
    while (c != NULL) {
        if (c->color == BLACK) {
            d++;
        }
        c = c->child[LEFT];
    }
    assertBlackNodes(tree->root, d);
}

