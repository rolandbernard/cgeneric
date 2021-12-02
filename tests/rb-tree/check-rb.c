
#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef TYPE
#include "rb-tree/rb-tree.h"
#endif

#define LEFT  0
#define RIGHT 1

#define BLACK false
#define RED   true

void blanks(int depth, int pos, bool left) {
    for (int i = 0; i < depth; i++) {
        if ((pos & (1 << (depth - 1 - i))) != 0) {
            if (i == depth - 1) {
                if (left) {
                    fprintf(stdout, "  ┌");
                } else {
                    fprintf(stdout, "  └");
                }
            } else {
                fprintf(stdout, "  │");
            }
        } else {
            fprintf(stdout, "   ");
        }
    }
}

void print(TYPED(RBTreeNode)* n, int depth, int pos, bool left) {
    if (n != NULL) {
        int keep = 2 * pos + 1;
        int leave = keep & ~0b10;
        print(n->child[RIGHT], depth + 1, left ? leave : keep, true);
        blanks(depth, pos, left);
        fprintf(stdout, "─%2d(%s)\n", n->value, n->color == RED ? "R" : "B");
        print(n->child[LEFT], depth + 1, left ? keep : leave, false);
    }
}

void printTree(TYPED(RBTreeNode)* n) {
    print(n, 0, 0, false);
}

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

