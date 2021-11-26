
#include <assert.h>
#include <stddef.h>

#include "b-tree.h"

void TYPED(initBTree)(TYPED(BTree)* tree) {
    tree->root = NULL;
}

static void TYPED(freeBTreeNodes)(TYPED(BTreeNode)* node) {
    if (node != NULL) {
        for (size_t i = 0; i <= node->count; i++) {
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
        size_t ret = node->count;
        for (size_t i = 0; i <= node->count; i++) {
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
#ifdef BINARY_SEARCH
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
#else
    size_t i = 0;
    while (i < size && LESS_THAN(array[i], value)) {
        i++;
    }
    return i;
#endif
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

static size_t TYPED(positionOfChild)(TYPED(BTreeNode)* parent, TYPED(BTreeNode)* child) {
#ifdef BINARY_SEARCH
    size_t i = TYPED(lowerBound)(parent->values, parent->count, child->values[0]);
#else
    size_t i = 0;
#endif
    while (parent != NULL && i <= parent->count && parent->child[i] != child) {
        i++;
    }
    return i;
}

static void TYPED(insertIntoBTreeNode)(
    TYPED(BTree)* tree, TYPED(BTreeNode)* node, TYPE value, TYPED(BTreeNode)* child, size_t at
) {
    if (node->count == CAPACITY) {
        TYPED(BTreeNode)* right = ZALLOC(TYPED(BTreeNode), 1);
        right->parent = node->parent;
        right->count = node->count - node->count / 2;
        for (size_t j = 0; j < right->count; j++) {
            right->values[j] = node->values[node->count / 2 + j];
            right->child[j] = node->child[node->count / 2 + j];
        }
        right->child[right->count] = node->child[node->count];
        TYPE median;
        if (at == node->count / 2) {
            median = value;
            right->child[0] = child;
        } else if (at < node->count / 2) {
            median = node->values[node->count / 2 - 1];
            for (size_t j = node->count / 2 - 1; j > at;) {
                j--;
                node->values[j + 1] = node->values[j];
                node->child[j + 2] = node->child[j + 1];
            }
            node->values[at] = value;
            node->child[at + 1] = child;
            if (child != NULL) {
                child->parent = node;
            }
        } else {
            median = right->values[0];
            for (size_t j = 0; j < at - 1 - node->count / 2; j++) {
                right->values[j] = right->values[j + 1];
                right->child[j] = right->child[j + 1];
            }
            right->child[at - 1 - node->count / 2] = right->child[at - node->count / 2];
            right->values[at - 1 - node->count / 2] = value;
            right->child[at - node->count / 2] = child;
        }
        if (right->child[0] != NULL) {
            for (size_t j = 0; j <= right->count; j++) {
                right->child[j]->parent = right;
            }
        }
        node->count /= 2;
        if (node->parent == NULL) {
            tree->root = ZALLOC(TYPED(BTreeNode), 1);
            tree->root->count = 1;
            tree->root->values[0] = median;
            tree->root->child[0] = node;
            node->parent = tree->root;
            tree->root->child[1] = right;
            right->parent = tree->root;
        } else {
            size_t i = TYPED(positionOfChild)(node->parent, node);
            TYPED(insertIntoBTreeNode)(tree, node->parent, median, right, i);
        }
    } else {
        for (size_t j = node->count; j > at;) {
            j--;
            node->values[j + 1] = node->values[j];
            node->child[j + 2] = node->child[j + 1];
        }
        node->values[at] = value;
        node->child[at + 1] = child;
        if (child != NULL) {
            child->parent = node;
        }
        node->count++;
    }
}

void TYPED(insertIntoBTree)(TYPED(BTree)* tree, TYPE element) {
    if (tree->root == NULL) {
        tree->root = ZALLOC(TYPED(BTreeNode), 1);
        tree->root->count = 1;
        tree->root->values[0] = element;
    } else {
        TYPED(BTreeNode)* p = NULL;
        TYPED(BTreeNode)* c = tree->root;
        size_t n = 0;
        while (c != NULL) {
            size_t d = TYPED(lowerBound)(c->values, c->count, element);
#ifdef IS_SET
            if (
                d < c->count && !LESS_THAN(c->values[d], element)
                && !LESS_THAN(element, c->values[d])
            ) {
                return;
            }
#endif
            n = d;
            p = c;
            c = c->child[d];
        }
        TYPED(insertIntoBTreeNode)(tree, p, element, NULL, n);
    }
}

static void TYPED(deleteRebalanceBTreeNode)(TYPED(BTree)* tree, TYPED(BTreeNode)* node) {
    if (node->count == 0 && node->parent == NULL) {
        tree->root = node->child[0];
        FREE(node);
    } else if (node->count < CAPACITY / 2 && node->parent != NULL) {
        size_t d = TYPED(positionOfChild)(node->parent, node);
        if (
            d > 0 && node->parent->child[d - 1] != NULL
            && node->parent->child[d - 1]->count > CAPACITY / 2
        ) {
            TYPED(BTreeNode)* sib = node->parent->child[d - 1];
            node->count++;
            for (size_t i = node->count; i > 1;) {
                i--;
                node->values[i] = node->values[i - 1];
                node->child[i + 1] = node->child[i];
            }
            node->child[1] = node->child[0];
            node->values[0] = node->parent->values[d - 1];
            node->child[0] = sib->child[sib->count];
            if (node->child[0] != NULL) {
                node->child[0]->parent = node;
            }
            node->parent->values[d - 1] = sib->values[sib->count - 1];
            sib->count--;
        } else if (
            d < node->parent->count && node->parent->child[d + 1] != NULL
            && node->parent->child[d + 1]->count > CAPACITY / 2
        ) {
            TYPED(BTreeNode)* sib = node->parent->child[d + 1];
            node->values[node->count] = node->parent->values[d];
            node->child[node->count + 1] = sib->child[0];
            if (node->child[node->count + 1] != NULL) {
                node->child[node->count + 1]->parent = node;
            }
            node->parent->values[d] = sib->values[0];
            node->count++;
            for (size_t i = 1; i < sib->count; i++) {
                sib->values[i - 1] = sib->values[i];
                sib->child[i - 1] = sib->child[i];
            }
            sib->child[sib->count - 1] = sib->child[sib->count];
            sib->count--;
        } else {
            TYPED(BTreeNode) * left;
            TYPED(BTreeNode) * right;
            if (d > 0) {
                left = node->parent->child[d - 1];
                right = node;
                d--;
            } else {
                left = node;
                right = node->parent->child[d + 1];
            }
            left->values[left->count] = node->parent->values[d];
            left->child[left->count + 1] = right->child[0];
            if (left->child[left->count + 1] != NULL) {
                left->child[left->count + 1]->parent = left;
            }
            left->count++;
            for (size_t i = 0; i < right->count; i++) {
                left->values[left->count] = right->values[i];
                left->child[left->count + 1] = right->child[i + 1];
                if (left->child[left->count + 1] != NULL) {
                    left->child[left->count + 1]->parent = left;
                }
                left->count++;
            }
            FREE(right);
            for (size_t i = d + 1; i < left->parent->count; i++) {
                left->parent->values[i - 1] = left->parent->values[i];
                left->parent->child[i] = left->parent->child[i + 1];
                if (left->parent->child[i] != NULL) {
                    left->parent->child[i]->parent = left->parent;
                }
            }
            left->parent->count--;
            TYPED(deleteRebalanceBTreeNode)(tree, left->parent);
        }
    }
}

static void TYPED(deleteFromBTreeNode)(TYPED(BTree)* tree, TYPED(BTreeNode)* node, size_t at) {
    if (node->child[at + 1] != NULL) {
        TYPED(BTreeNode)* c = node->child[at + 1];
        while (c->child[0] != NULL) {
            c = c->child[0];
        }
        node->values[at] = c->values[0];
        TYPED(deleteFromBTreeNode)(tree, c, 0);
    } else {
        for (size_t i = at + 1; i < node->count; i++) {
            node->values[i - 1] = node->values[i];
        }
        node->count--;
        TYPED(deleteRebalanceBTreeNode)(tree, node);
    }
}

void TYPED(deleteFromBTree)(TYPED(BTree)* tree, TYPE element) {
    if (tree->root != NULL) {
        TYPED(BTreeNode)* c = tree->root;
        while (c != NULL) {
            size_t d = TYPED(lowerBound)(c->values, c->count, element);
            if (
                d < c->count && !LESS_THAN(c->values[d], element)
                && !LESS_THAN(element, c->values[d])
            ) {
                TYPED(deleteFromBTreeNode)(tree, c, d);
                return;
            }
            c = c->child[d];
        }
    }
}

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

TYPE TYPED(getNextBTree)(TYPED(BTreeIterator)* iter) {
    TYPE ret = iter->current->values[iter->n];
    iter->n++;
    if (iter->current->child[iter->n] != NULL) {
        TYPED(BTreeNode)* c = iter->current->child[iter->n];
        while (c->child[0] != NULL) {
            c = c->child[0];
        }
        iter->current = c;
        iter->n = 0;
    } else if (iter->n >= iter->current->count) {
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

