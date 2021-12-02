
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
        return 1 + TYPED(countRBTreeNodes)(node->child[LEFT])
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
    while (c != NULL) {
        if (LESS_THAN(element, c->value)) {
            c = c->child[LEFT];
        } else if (LESS_THAN(c->value, element)) {
            c = c->child[RIGHT];
        } else {
            return true;
        }
    }
    return false;
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
    while (c->parent != NULL) {
        TYPED(RBTreeNode)* p = c->parent;
        if (p->color == BLACK) {
            return;
        }
        if (p->parent == NULL) {
            p->color = BLACK;
            return;
        }
        TYPED(RBTreeNode)* g = p->parent;
        int dir = g->child[LEFT] == p ? LEFT : RIGHT;
        TYPED(RBTreeNode)* u = g->child[1 - dir];
        if (u == NULL || u->color == BLACK) {
            if (c == p->child[1 - dir]) {
                TYPED(rotateRBTree)(tree, p, dir);
                c = p;
                p = g->child[dir];
            }
            TYPED(rotateRBTree)(tree, g, 1 - dir);
            p->color = BLACK;
            g->color = RED;
            return;
        }
        p->color = BLACK;
        u->color = BLACK;
        g->color = RED;
        c = g;
    }
}

#ifdef IS_MAP
void TYPED(putInRBTree)(TYPED(RBTree)* tree, TYPE key, VALUE value) {
    if (tree->root == NULL) {
        tree->root = ZALLOC(TYPED(RBTreeNode), 1);
        tree->root->color = RED;
        tree->root->value = key;
        tree->root->val = value;
    } else {
        TYPED(RBTreeNode)* p = NULL;
        TYPED(RBTreeNode)* c = tree->root;
        int dir = 0;
        while (c != NULL) {
            p = c;
            if (LESS_THAN(key, c->value)) {
                c = c->child[LEFT];
                dir = LEFT;
            } else if (LESS_THAN(c->value, key)) {
                c = c->child[RIGHT];
                dir = RIGHT;
            } else {
                c->val = value;
                return;
            }
        }
        p->child[dir] = ZALLOC(TYPED(RBTreeNode), 1);
        p->child[dir]->color = RED;
        p->child[dir]->parent = p;
        p->child[dir]->value = key;
        p->child[dir]->val = value;
        TYPED(insertRebalanceRBTree)(tree, p->child[dir]);
    }
}

VALUE TYPED(getFromRBTree)(TYPED(RBTree)* tree, TYPE key) {
    TYPED(RBTreeNode)* c = tree->root;
    while (c != NULL) {
        if (LESS_THAN(key, c->value)) {
            c = c->child[LEFT];
        } else if (LESS_THAN(c->value, key)) {
            c = c->child[RIGHT];
        } else {
            return c->val;
        }
    }
    return DEFAULT;
}
#else
void TYPED(insertIntoRBTree)(TYPED(RBTree)* tree, TYPE element) {
    if (tree->root == NULL) {
        tree->root = ZALLOC(TYPED(RBTreeNode), 1);
        tree->root->color = RED;
        tree->root->value = element;
    } else {
        TYPED(RBTreeNode)* p = NULL;
        TYPED(RBTreeNode)* c = tree->root;
        int dir = 0;
        while (c != NULL) {
            p = c;
            if (LESS_THAN(element, c->value)) {
                c = c->child[LEFT];
                dir = LEFT;
#ifdef IS_SET
            } else if (LESS_THAN(c->value, element)) {
                c = c->child[RIGHT];
                dir = RIGHT;
            } else {
                return;
            }
#else
            } else {
                c = c->child[RIGHT];
                dir = RIGHT;
            }
#endif
        }
        p->child[dir] = ZALLOC(TYPED(RBTreeNode), 1);
        p->child[dir]->color = RED;
        p->child[dir]->parent = p;
        p->child[dir]->value = element;
        TYPED(insertRebalanceRBTree)(tree, p->child[dir]);
    }
}
#endif

static TYPED(RBTreeNode)* TYPED(replacementForRBTreeNode)(TYPED(RBTreeNode)* node) {
    if (node->child[LEFT] != NULL && node->child[RIGHT] != NULL) {
        TYPED(RBTreeNode)* c = node->child[RIGHT];
        while (c->child[LEFT] != NULL) {
            c = c->child[LEFT];
        }
        return c;
    } else if (node->child[LEFT] == NULL && node->child[RIGHT] == NULL) {
        return NULL;
    } else if (node->child[LEFT] != NULL) {
        return node->child[LEFT];
    } else {
        return node->child[RIGHT];
    }
}

static void TYPED(fixDoubleBlackRBTreeNode)(TYPED(RBTree)* tree, TYPED(RBTreeNode)* node) {
    while (node != tree->root) {
        int dir = node->parent->child[LEFT] == node ? LEFT : RIGHT;
        TYPED(RBTreeNode)* sibling = node->parent->child[1 - dir];
        if (sibling == NULL) {
            node = node->parent;
        } else if (sibling->color == RED) {
            node->parent->color = RED;
            sibling->color = BLACK;
            TYPED(rotateRBTree)(tree, node->parent, dir);
        } else if (
            (sibling->child[LEFT] != NULL && sibling->child[LEFT]->color == RED)
            || (sibling->child[RIGHT] != NULL && sibling->child[RIGHT]->color == RED)
        ) {
            if (sibling->child[dir] != NULL && sibling->child[dir]->color == RED) {
                sibling->child[dir]->color = node->parent->color;
                TYPED(rotateRBTree)(tree, sibling, 1 - dir);
                TYPED(rotateRBTree)(tree, node->parent, dir);
            } else {
                sibling->child[1 - dir]->color = sibling->color;
                sibling->color = node->parent->color;
                TYPED(rotateRBTree)(tree, node->parent, dir);
            }
            node->parent->color = BLACK;
            return;
        } else {
            sibling->color = RED;
            if (node->parent->color == BLACK) {
                node = node->parent;
            } else {
                node->parent->color = BLACK;
                return;
            }
        }
    }
}

static void TYPED(removeRBTreeNode)(TYPED(RBTree)* tree, TYPED(RBTreeNode)* node) {
    TYPED(RBTreeNode)* rep = TYPED(replacementForRBTreeNode)(node);
    bool bothBlack = (rep == NULL || rep->color == BLACK) && node->color == BLACK;
    if (rep == NULL) {
        if (node == tree->root) {
            tree->root = NULL;
        } else {
            int dir = node->parent->child[LEFT] == node ? LEFT : RIGHT;
            if (bothBlack) {
                TYPED(fixDoubleBlackRBTreeNode)(tree, node);
            } else if (node->parent->child[1 - dir] != NULL) {
                node->parent->child[1 - dir]->color = RED;
            }
            node->parent->child[dir] = NULL;
        }
        FREE(node);
    } else if (node->child[LEFT] == NULL || node->child[RIGHT] == NULL) {
        if (node == tree->root) {
            node->value = rep->value;
#ifdef IS_MAP
            node->val = rep->val;
#endif
            node->child[LEFT] = NULL;
            node->child[RIGHT] = NULL;
            FREE(rep);
        } else {
            int dir = node->parent->child[LEFT] == node ? LEFT : RIGHT;
            node->parent->child[dir] = rep;
            rep->parent = node->parent;
            FREE(node);
            if (bothBlack) {
                TYPED(fixDoubleBlackRBTreeNode)(tree, rep);
            } else {
                rep->color = BLACK;
            }
        }
    } else {
        node->value = rep->value;
#ifdef IS_MAP
        node->val = rep->val;
#endif
        TYPED(removeRBTreeNode)(tree, rep);
    }
}

void TYPED(deleteFromRBTree)(TYPED(RBTree)* tree, TYPE element) {
    if (tree->root != NULL) {
        TYPED(RBTreeNode)* c = tree->root;
        while (c != NULL) {
            if (LESS_THAN(element, c->value)) {
                c = c->child[LEFT];
            } else if (LESS_THAN(c->value, element)) {
                c = c->child[RIGHT];
            } else {
                break;
            }
        }
        if (c != NULL) {
            TYPED(removeRBTreeNode)(tree, c);
        }
    }
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

TYPED(RBTreeIterator) TYPED(getRBTreeIteratorAt)(TYPED(RBTree)* tree, TYPE k) {
    TYPED(RBTreeNode)* p = NULL;
    TYPED(RBTreeNode)* c = tree->root;
    while (c != NULL) {
        if (!LESS_THAN(c->value, k) && (p == NULL || !LESS_THAN(p->value, c->value))) {
            p = c;
        }
        if (LESS_THAN(k, c->value)) {
            c = c->child[LEFT];
        } else {
            c = c->child[RIGHT];
        }
    }
    TYPED(RBTreeIterator) ret = {
        .current = p,
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

