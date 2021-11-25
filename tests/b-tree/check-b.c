
#include <assert.h>
#include <stddef.h>

#ifndef TYPE
#include "b-tree/b-tree.h"
#endif

void assertNodes(TYPED(BTreeNode)* node) {
    if (node != NULL) {
        assert(node->count <= CAPACITY);
        assert(node->child[0] == NULL || node->count >= node->count / 2);
        for (size_t i = 1; i < node->count; i++) {
            assert(!LESS_THAN(node->values[i], node->values[i - 1]));
        }
        for (size_t i = 0; i < node->count; i++) {
            assert(node->child[i] == NULL || !LESS_THAN(node->values[i], node->child[i]->values[node->child[i]->count - 1]));
            assert(node->child[i + 1] == NULL || !LESS_THAN(node->child[i + 1]->values[0], node->values[i]));
        }
        for (size_t i = 0; i <= node->count; i++) {
            if (node->child[0] == NULL) {
                assert(node->child[i] == NULL);
            } else {
                assert(node->child[i] != NULL);
                assert(node->child[i]->parent == node);
            }
        }
        for (size_t i = 0; i <= node->count; i++) {
            assertNodes(node->child[i]);
        }
    }
}

size_t height(TYPED(BTreeNode)* node) {
    if (node == NULL) {
        return 0;
    } else {
        return 1 + height(node->child[0]);
    }
}

void assertHeight(TYPED(BTreeNode)* node, size_t h) {
    if (node == NULL) {
        assert(h == 0);
    } else {
        for (size_t i = 0; i <= node->count; i++) {
            assertHeight(node->child[i], h - 1);
        }
    }
}

void isBTree(TYPED(BTree)* tree) {
    assert(tree->root->child[0] == NULL || tree->root->count >= 1);
    assertNodes(tree->root);
    assertHeight(tree->root, height(tree->root));
}

