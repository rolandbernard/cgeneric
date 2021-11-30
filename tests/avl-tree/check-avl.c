
#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef TYPE
#include "avl-tree/avl-tree.h"
#endif

#define LEFT  0
#define RIGHT 1

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

void print(TYPED(AvlTreeNode)* n, int depth, int pos, bool left) {
    if (n != NULL) {
        int keep = 2 * pos + 1;
        int leave = keep & ~0b10;
        print(n->child[RIGHT], depth + 1, left ? leave : keep, true);
        blanks(depth, pos, left);
        fprintf(stdout, "─%2d(%i)\n", n->value, n->balance);
        print(n->child[LEFT], depth + 1, left ? keep : leave, false);
    }
}

void printTree(TYPED(AvlTreeNode)* n) {
    print(n, 0, 0, false);
}

#define MAX(A, B) ((A) < (B) ? (B) : (A))

int assertNodes(TYPED(AvlTreeNode)* node) {
    if (node != NULL) {
        assert(node->child[LEFT] == NULL || node->child[LEFT]->parent == node);
        assert(node->child[LEFT] == NULL || !LESS_THAN(node->value, node->child[LEFT]->value));
        assert(node->child[RIGHT] == NULL || node->child[RIGHT]->parent == node);
        assert(node->child[RIGHT] == NULL || !LESS_THAN(node->child[RIGHT]->value, node->value));
        int left = assertNodes(node->child[LEFT]);
        int right = assertNodes(node->child[RIGHT]);
        assert(right - left == node->balance);
        assert(abs(left - right) <= 1);
        return 1 + MAX(left, right);
    } else {
        return 0;
    }
}

void isAvlTree(TYPED(AvlTree)* tree) {
    assert(tree->root == NULL || tree->root->parent == NULL);
    assertNodes(tree->root);
}

