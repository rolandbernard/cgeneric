
#include <stddef.h>
#include <stdbool.h>

#include "default.h"

typedef struct TYPED(ForwardList) TYPED(ForwardList);

typedef struct TYPED(ForwardListElement) TYPED(ForwardListElement);

struct TYPED(ForwardListElement) {
    TYPED(ForwardListElement)* next;
    TYPE value;
};

struct TYPED(ForwardList) {
    TYPED(ForwardListElement)* head;
};

void TYPED(initForwardList)(TYPED(ForwardList)* list);

void TYPED(deinitForwardList)(TYPED(ForwardList)* list);

size_t TYPED(sizeOfForwardList)(TYPED(ForwardList)* list);

void TYPED(pushFrontToForwardList)(TYPED(ForwardList)* list, TYPE element);

TYPE TYPED(popFrontFromForwardList)(TYPED(ForwardList)* list);

TYPE TYPED(getFromForwardList)(TYPED(ForwardList)* list, size_t i);

void TYPED(setInForwardList)(TYPED(ForwardList)* list, size_t i, TYPE element);

typedef struct TYPED(ForwardListIterator) TYPED(ForwardListIterator);

struct TYPED(ForwardListIterator) {
    TYPED(ForwardListElement)* elem;
};

TYPED(ForwardListIterator) TYPED(getForwardListIterator)(TYPED(ForwardList)* list);

bool TYPED(hasNextForwardList)(TYPED(ForwardListIterator)* iter);

TYPE TYPED(getNextForwardList)(TYPED(ForwardListIterator)* iter);

