
#include <stddef.h>
#include <stdbool.h>

#include "default.h"

typedef struct TYPED(BTree) TYPED(BTree);

typedef struct TYPED(BTreeNode) TYPED(BTreeNode);

struct TYPED(BTreeNode) {
    TYPED(BTreeNode)* parent;
    size_t count;
    TYPED(BTreeNode)* child[CAPACITY + 1];
    TYPE values[CAPACITY];
};

struct TYPED(BTree) {
    TYPED(BTreeNode)* root;
};

void TYPED(initBTree)(TYPED(BTree)* tree);

void TYPED(deinitBTree)(TYPED(BTree)* tree);

size_t TYPED(sizeOfBTree)(TYPED(BTree)* tree);

TYPE TYPED(firstBTree)(TYPED(BTree)* tree);

TYPE TYPED(lastBTree)(TYPED(BTree)* tree);

bool TYPED(hasInBTree)(TYPED(BTree)* tree, TYPE element);

void TYPED(insertIntoBTree)(TYPED(BTree)* tree, TYPE element);

void TYPED(deleteFromBTree)(TYPED(BTree)* tree, TYPE element);

typedef struct TYPED(BTreeIterator) TYPED(BTreeIterator);

struct TYPED(BTreeIterator) {
    TYPED(BTreeNode)* current;
    size_t n;
};

TYPED(BTreeIterator) TYPED(getBTreeIterator)(TYPED(BTree)* tree);

TYPED(BTreeIterator) TYPED(getBTreeIteratorAt)(TYPED(BTree)* tree, TYPE k);

bool TYPED(hasNextBTree)(TYPED(BTreeIterator)* iter);

TYPE TYPED(getNextBTree)(TYPED(BTreeIterator)* iter);

