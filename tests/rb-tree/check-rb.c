
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
        assert(node->child[LEFT] == NULL || node->child[LEFT]->parent == node);
        assert(node->child[LEFT] == NULL || !LESS_THAN(node->value, node->child[LEFT]->value));
        assert(node->child[RIGHT] == NULL || node->child[RIGHT]->parent == node);
        assert(node->child[RIGHT] == NULL || !LESS_THAN(node->child[RIGHT]->value, node->value));
    }
}

void isRBTree(TYPED(RBTree)* tree) {
    assert(tree->root == NULL || tree->root->parent == NULL);
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

