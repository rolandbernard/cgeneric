
#include <assert.h>
#include <stddef.h>

#include "avl-tree.h"

#define LEFT  0
#define RIGHT 1

void TYPED(initAvlTree)(TYPED(AvlTree)* tree) {
    tree->root = NULL;
}

static void TYPED(freeAvlTreeNodes)(TYPED(AvlTreeNode)* node) {
    if (node != NULL) {
        TYPED(freeAvlTreeNodes)(node->child[LEFT]);
        TYPED(freeAvlTreeNodes)(node->child[RIGHT]);
        FREE(node);
    }
}

void TYPED(deinitAvlTree)(TYPED(AvlTree)* tree) {
    TYPED(freeAvlTreeNodes)(tree->root);
    tree->root = NULL;
}

static size_t TYPED(countAvlTreeNodes)(TYPED(AvlTreeNode)* node) {
    if (node != NULL) {
        return 1 + TYPED(countAvlTreeNodes)(node->child[LEFT])
               + TYPED(countAvlTreeNodes)(node->child[RIGHT]);
    } else {
        return 0;
    }
}

size_t TYPED(sizeOfAvlTree)(TYPED(AvlTree)* tree) {
    return TYPED(countAvlTreeNodes)(tree->root);
}

TYPE TYPED(firstAvlTree)(TYPED(AvlTree)* tree) {
    TYPED(AvlTreeNode)* c = tree->root;
    while (c->child[LEFT] != NULL) {
        c = c->child[LEFT];
    }
    return c->value;
}

TYPE TYPED(lastAvlTree)(TYPED(AvlTree)* tree) {
    TYPED(AvlTreeNode)* c = tree->root;
    while (c->child[RIGHT] != NULL) {
        c = c->child[RIGHT];
    }
    return c->value;
}

bool TYPED(hasInAvlTree)(TYPED(AvlTree)* tree, TYPE element) {
    TYPED(AvlTreeNode)* c = tree->root;
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

static TYPED(AvlTreeNode)* TYPED(rotateAvlTree)(TYPED(AvlTree)* tree, TYPED(AvlTreeNode)* root, int dir) {
    TYPED(AvlTreeNode)* root_parent = root->parent;
    TYPED(AvlTreeNode)* new_root = root->child[1 - dir];
    TYPED(AvlTreeNode)* to_reparent = new_root->child[dir];
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
    return new_root;
}

static void TYPED(insertRebalanceAvlTree)(TYPED(AvlTree)* tree, TYPED(AvlTreeNode)* inserted) {
    TYPED(AvlTreeNode)* c = inserted;
    TYPED(AvlTreeNode)* p = inserted->parent;
    while (p != NULL) {
        int dir = (c == p->child[RIGHT] ? RIGHT : LEFT);
        int bal = dir == RIGHT ? 1 : -1;
        if (p->balance == bal) {
            if (c->balance == -bal) {
                TYPED(rotateAvlTree)(tree, c, dir);
                TYPED(AvlTreeNode)* n = TYPED(rotateAvlTree)(tree, p, 1 - dir);
                if (n->balance == 0) {
                    p->balance = 0;
                    c->balance = 0;
                } else if (n->balance == bal) {
                    p->balance = -bal;
                    c->balance = 0;
                } else {
                    p->balance = 0;
                    c->balance = bal;
                }
                n->balance = 0;
            } else {
                TYPED(AvlTreeNode)* n = TYPED(rotateAvlTree)(tree, p, 1 - dir);
                if (n->balance == 0) {
                    n->balance = -bal;
                    p->balance = bal;
                } else {
                    n->balance = 0;
                    p->balance = 0;
                }
            }
            return;
        } else if (p->balance == -bal) {
            p->balance = 0;
            return;
        } else {
            p->balance = bal;
        }
        c = p;
        p = p->parent;
    }
}

void TYPED(insertIntoAvlTree)(TYPED(AvlTree)* tree, TYPE element) {
    if (tree->root == NULL) {
        tree->root = ZALLOC(TYPED(AvlTreeNode), 1);
        tree->root->balance = 0;
        tree->root->value = element;
    } else {
        TYPED(AvlTreeNode)* p = NULL;
        TYPED(AvlTreeNode)* c = tree->root;
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
        p->child[dir] = ZALLOC(TYPED(AvlTreeNode), 1);
        p->child[dir]->balance = 0;
        p->child[dir]->parent = p;
        p->child[dir]->value = element;
        TYPED(insertRebalanceAvlTree)(tree, p->child[dir]);
    }
}

static TYPED(AvlTreeNode)* TYPED(replacementForAvlTreeNode)(TYPED(AvlTreeNode)* node) {
    if (node->child[LEFT] != NULL && node->child[RIGHT] != NULL) {
        TYPED(AvlTreeNode)* c = node->child[RIGHT];
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

static void TYPED(removeRebalanceAvlTree)(TYPED(AvlTree)* tree, TYPED(AvlTreeNode)* decreased) {
    TYPED(AvlTreeNode)* c = decreased;
    TYPED(AvlTreeNode)* p = decreased->parent;
    while (p != NULL) {
        int dir = (c == p->child[RIGHT] ? RIGHT : LEFT);
        int bal = dir == RIGHT ? -1 : 1;
        if (p->balance == bal) {
            TYPED(AvlTreeNode)* s = p->child[1 - dir];
            int b = s->balance;
            if (b == -bal) {
                TYPED(rotateAvlTree)(tree, s, 1 - dir);
                TYPED(AvlTreeNode)* n = TYPED(rotateAvlTree)(tree, p, dir);
                if (n->balance == 0) {
                    p->balance = 0;
                    s->balance = 0;
                } else if (n->balance == bal) {
                    p->balance = -bal;
                    s->balance = 0;
                } else {
                    p->balance = 0;
                    s->balance = bal;
                }
                n->balance = 0;
                p = n;
            } else {
                TYPED(AvlTreeNode)* n = TYPED(rotateAvlTree)(tree, p, dir);
                if (n->balance == 0) {
                    n->balance = -bal;
                    p->balance = bal;
                } else {
                    n->balance = 0;
                    p->balance = 0;
                }
                p = n;
            }
            if (b == 0) {
                return;
            }
        } else if (p->balance == -bal) {
            p->balance = 0;
        } else {
            p->balance = bal;
            return;
        }
        c = p;
        p = p->parent;
    }
}

static void TYPED(removeAvlTreeNode)(TYPED(AvlTree)* tree, TYPED(AvlTreeNode)* node) {
    TYPED(AvlTreeNode)* rep = TYPED(replacementForAvlTreeNode)(node);
    if (rep == NULL) {
        if (node == tree->root) {
            tree->root = NULL;
        } else {
            TYPED(removeRebalanceAvlTree)(tree, node);
            int dir = node->parent->child[LEFT] == node ? LEFT : RIGHT;
            node->parent->child[dir] = NULL;
        }
        FREE(node);
    } else if (node->child[LEFT] == NULL || node->child[RIGHT] == NULL) {
        if (node == tree->root) {
            node->value = rep->value;
            node->child[LEFT] = NULL;
            node->child[RIGHT] = NULL;
            FREE(rep);
        } else {
            int dir = node->parent->child[LEFT] == node ? LEFT : RIGHT;
            node->parent->child[dir] = rep;
            rep->parent = node->parent;
            TYPED(removeRebalanceAvlTree)(tree, rep);
            FREE(node);
        }
    } else {
        TYPE tmp = rep->value;
        rep->value = node->value;
        node->value = tmp;
        TYPED(removeAvlTreeNode)(tree, rep);
    }
}

void TYPED(deleteFromAvlTree)(TYPED(AvlTree)* tree, TYPE element) {
    if (tree->root != NULL) {
        TYPED(AvlTreeNode)* c = tree->root;
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
            TYPED(removeAvlTreeNode)(tree, c);
        }
    }
}

TYPED(AvlTreeIterator) TYPED(getAvlTreeIterator)(TYPED(AvlTree)* tree) {
    TYPED(AvlTreeNode)* c = tree->root;
    while (c->child[LEFT] != NULL) {
        c = c->child[LEFT];
    }
    TYPED(AvlTreeIterator) ret = {
        .current = c,
    };
    return ret;
}

TYPED(AvlTreeIterator) TYPED(getAvlTreeIteratorAt)(TYPED(AvlTree)* tree, TYPE k) {
    TYPED(AvlTreeNode)* p = NULL;
    TYPED(AvlTreeNode)* c = tree->root;
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
    TYPED(AvlTreeIterator) ret = {
        .current = p,
    };
    return ret;
}

bool TYPED(hasNextAvlTree)(TYPED(AvlTreeIterator)* iter) {
    return iter->current != NULL;
}

TYPE TYPED(getNextAvlTree)(TYPED(AvlTreeIterator)* iter) {
    TYPE ret = iter->current->value;
    if (iter->current->child[RIGHT] != NULL) {
        TYPED(AvlTreeNode)* c = iter->current->child[RIGHT];
        while (c->child[LEFT] != NULL) {
            c = c->child[LEFT];
        }
        iter->current = c;
    } else {
        TYPED(AvlTreeNode)* parent = iter->current->parent;
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

