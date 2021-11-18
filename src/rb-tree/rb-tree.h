
#include <stddef.h>
#include <stdbool.h>

#include "default.h"

typedef struct TYPED(RBTree) TYPED(RBTree);

typedef struct TYPED(RBTreeNode) TYPED(RBTreeNode);

struct TYPED(RBTreeNode) {
    TYPED(RBTreeNode)* parent;
    TYPED(RBTreeNode)* child[2];
    TYPE value;
    bool color;
};

struct TYPED(RBTree) {
    TYPED(RBTreeNode)* root;
};

void TYPED(initRBTree)(TYPED(RBTree)* tree);

void TYPED(deinitRBTree)(TYPED(RBTree)* tree);

size_t TYPED(sizeOfRBTree)(TYPED(RBTree)* tree);

TYPE TYPED(firstRBTree)(TYPED(RBTree)* tree);

TYPE TYPED(lastRBTree)(TYPED(RBTree)* tree);

void TYPED(insertIntoRBTree)(TYPED(RBTree)* tree, TYPE element);

bool TYPED(hasInRBTree)(TYPED(RBTree)* tree, TYPE element);

void TYPED(deleteFromRBTree)(TYPED(RBTree)* tree, TYPE element);

typedef struct TYPED(RBTreeIterator) TYPED(RBTreeIterator);

struct TYPED(RBTreeIterator) {
    TYPED(RBTreeNode)* current;
};

TYPED(RBTreeIterator) TYPED(getRBTreeIterator)(TYPED(RBTree)* tree);

bool TYPED(hasNextRBTree)(TYPED(RBTreeIterator)* iter);

TYPE TYPED(getNextRBTree)(TYPED(RBTreeIterator)* iter);

