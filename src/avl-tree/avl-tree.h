
#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

#include "default.h"

typedef struct TYPED(AvlTree) TYPED(AvlTree);

typedef struct TYPED(AvlTreeNode) TYPED(AvlTreeNode);

struct TYPED(AvlTreeNode) {
    TYPED(AvlTreeNode)* parent;
    TYPED(AvlTreeNode)* child[2];
    TYPE value;
#ifdef IS_MAP
    VALUE val;
#endif
    int8_t balance;
};

struct TYPED(AvlTree) {
    TYPED(AvlTreeNode)* root;
};

void TYPED(initAvlTree)(TYPED(AvlTree)* tree);

void TYPED(deinitAvlTree)(TYPED(AvlTree)* tree);

size_t TYPED(sizeOfAvlTree)(TYPED(AvlTree)* tree);

TYPE TYPED(firstAvlTree)(TYPED(AvlTree)* tree);

TYPE TYPED(lastAvlTree)(TYPED(AvlTree)* tree);

#ifdef IS_MAP
void TYPED(putInAvlTree)(TYPED(AvlTree)* tree, TYPE key, VALUE value);

VALUE TYPED(getFromAvlTree)(TYPED(AvlTree)* tree, TYPE key);
#else
void TYPED(insertIntoAvlTree)(TYPED(AvlTree)* tree, TYPE element);
#endif

bool TYPED(hasInAvlTree)(TYPED(AvlTree)* tree, TYPE element);

void TYPED(deleteFromAvlTree)(TYPED(AvlTree)* tree, TYPE element);

typedef struct TYPED(AvlTreeIterator) TYPED(AvlTreeIterator);

struct TYPED(AvlTreeIterator) {
    TYPED(AvlTreeNode)* current;
};

TYPED(AvlTreeIterator) TYPED(getAvlTreeIterator)(TYPED(AvlTree)* tree);

TYPED(AvlTreeIterator) TYPED(getAvlTreeIteratorAt)(TYPED(AvlTree)* tree, TYPE k);

bool TYPED(hasNextAvlTree)(TYPED(AvlTreeIterator)* iter);

TYPE TYPED(getNextAvlTree)(TYPED(AvlTreeIterator)* iter);

