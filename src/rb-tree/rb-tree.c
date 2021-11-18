
#include <assert.h>
#include <stddef.h>

#include "rb-tree.h"

#define LEFT  0
#define RIGHT 1

#define BLACK false
#define RED   true

void TYPED(initRBTree)(TYPED(RBTree)* tree) {
    tree->root = NULL;
}

static void TYPED(freeRBTreeNodes)(TYPED(RBTreeNode)* node) {
    if (node != NULL) {
        TYPED(freeRBTreeNodes)(node->child[LEFT]);
        TYPED(freeRBTreeNodes)(node->child[RIGHT]);
        FREE(node);
    }
}

void TYPED(deinitRBTree)(TYPED(RBTree)* tree) {
    TYPED(freeRBTreeNodes)(tree->root);
    tree->root = NULL;
}

static size_t TYPED(countRBTreeNodes)(TYPED(RBTreeNode)* node) {
    if (node != NULL) {
        return TYPED(countRBTreeNodes)(node->child[LEFT])
               + TYPED(countRBTreeNodes)(node->child[RIGHT]);
    } else {
        return 0;
    }
}

size_t TYPED(sizeOfRBTree)(TYPED(RBTree)* tree) {
    return TYPED(countRBTreeNodes)(tree->root);
}

TYPE TYPED(firstRBTree)(TYPED(RBTree)* tree) {
    TYPED(RBTreeNode)* c = tree->root;
    while (c->child[LEFT] != NULL) {
        c = c->child[LEFT];
    }
    return c->value;
}

TYPE TYPED(lastRBTree)(TYPED(RBTree)* tree) {
    TYPED(RBTreeNode)* c = tree->root;
    while (c->child[RIGHT] != NULL) {
        c = c->child[RIGHT];
    }
    return c->value;
}

bool TYPED(hasInRBTree)(TYPED(RBTree)* tree, TYPE element) {
    TYPED(RBTreeNode)* c = tree->root;
    while (c != NULL && c->value != element) {
        if (LESS_EQUAL(c->value, element)) {
            c = c->child[LEFT];
        } else {
            c = c->child[RIGHT];
        }
    }
    return c != NULL && c->value == element;
}

static void TYPED(rotateRBTree)(TYPED(RBTree)* tree, TYPED(RBTreeNode)* root, int dir) {
    TYPED(RBTreeNode)* root_parent = root->parent;
    TYPED(RBTreeNode)* new_root = root->child[1 - dir];
    TYPED(RBTreeNode)* to_reparent = new_root->child[dir];
    root->child[RIGHT - dir] = to_reparent;
    if (to_reparent != NULL) {
        to_reparent->parent = root;
    }
    new_root->child[dir] = root;
    root->parent = new_root;
    new_root->parent = root_parent;
    if (root_parent != NULL) {
        root_parent->child[root == root_parent->child[LEFT] ? LEFT : RIGHT] = new_root;
    } else {
        tree->root = new_root;
    }
}

static void TYPED(insertRebalanceRBTree)(TYPED(RBTree)* tree, TYPED(RBTreeNode)* inserted) {
    TYPED(RBTreeNode)* c = inserted;
    do {
        if (c->parent == NULL || c->parent->color == BLACK) {
            return;
        }
        if (c->parent->parent == NULL) {
            c->parent->color = BLACK;
            return;
        }
        int dir = c->parent->parent->child[LEFT] == c->parent ? LEFT : RIGHT;
        TYPED(RBTreeNode)* u = c->parent->parent->child[1 - dir];
        if (u == NULL || u->color == BLACK) {
            if (c == c->parent->child[1 - dir]) {
                c = c->parent;
                TYPED(rotateRBTree)(tree, c, dir);
            }
            c->parent->parent->color = RED;
            c->parent->color = BLACK;
            TYPED(rotateRBTree)(tree, c->parent->parent, 1 - dir);
            return;
        }
        c->parent->color = BLACK;
        u->color = BLACK;
        c->parent->parent->color = RED;
        c = c->parent->parent;
    } while (c->parent != NULL);
}

void TYPED(insertIntoRBTree)(TYPED(RBTree)* tree, TYPE element) {
    TYPED(RBTreeNode)* p = NULL;
    TYPED(RBTreeNode)* c = tree->root;
    int dir = 0;
    while (c != NULL) {
        p = c;
        if (LESS_EQUAL(c->value, element)) {
            c = c->child[LEFT];
            dir = LEFT;
        } else {
            c = c->child[RIGHT];
            dir = RIGHT;
        }
    }
    if (p == NULL) {
        tree->root = ZALLOC(TYPED(RBTreeNode), 1);
        tree->root->color = RED;
        tree->root->value = element;
    } else {
        p->child[dir] = ZALLOC(TYPED(RBTreeNode), 1);
        p->child[dir]->color = RED;
        p->child[dir]->parent = p;
        p->child[dir]->value = element;
        TYPED(insertRebalanceRBTree)(tree, p->child[dir]);
    }
}

void TYPED(removeFromRBTree)(TYPED(RBTree)* tree, TYPE* elements) {
    // TODO
}

TYPED(RBTreeIterator) TYPED(getRBTreeIterator)(TYPED(RBTree)* tree) {
    TYPED(RBTreeNode)* c = tree->root;
    while (c->child[LEFT] != NULL) {
        c = c->child[LEFT];
    }
    TYPED(RBTreeIterator) ret = {
        .current = c,
    };
    return ret;
}

bool TYPED(hasNextRBTree)(TYPED(RBTreeIterator)* iter) {
    return iter->current != NULL;
}

TYPE TYPED(getNextRBTree)(TYPED(RBTreeIterator)* iter) {
    TYPE ret = iter->current->value;
    if (iter->current->child[RIGHT] != NULL) {
        TYPED(RBTreeNode)* c = iter->current->child[RIGHT];
        while (c->child[LEFT] != NULL) {
            c = c->child[LEFT];
        }
        iter->current = c;
    } else {
        TYPED(RBTreeNode)* parent = iter->current->parent;
        while (parent != NULL && parent->child[RIGHT] == iter->current) {
            iter->current = parent;
            parent = iter->current->parent;
        }
        iter->current = parent;
    }
    return ret;
}

#undef LEFT
#undef RIGHT

#undef BLACK
#undef RED

