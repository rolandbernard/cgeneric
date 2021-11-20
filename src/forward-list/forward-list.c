
#include <assert.h>
#include <stddef.h>

#include "forward-list.h"

void TYPED(initForwardList)(TYPED(ForwardList)* list) {
    list->head = NULL;
}

void TYPED(deinitForwardList)(TYPED(ForwardList)* list) {
    TYPED(ForwardListElement)* current = list->head;
    while (current != NULL) {
        TYPED(ForwardListElement)* to_free = current;
        current = to_free->next;
        FREE(to_free);
    }
    list->head = NULL;
}

size_t TYPED(sizeOfForwardList)(TYPED(ForwardList)* list) {
    size_t size = 0;
    TYPED(ForwardListElement)* current = list->head;
    while (current != NULL) {
        size++;
        current = current->next;
    }
    return size;
}

void TYPED(pushFrontToForwardList)(TYPED(ForwardList)* list, TYPE element) {
    TYPED(ForwardListElement)* new = ALLOC(TYPED(ForwardListElement), 1);
    new->value = element;
    new->next = list->head;
    list->head = new;
}

TYPE TYPED(popFrontFromForwardList)(TYPED(ForwardList)* list) {
    if (list->head != NULL) {
        TYPED(ForwardListElement)* removed = list->head;
        list->head = removed->next;
        TYPE ret = removed->value;
        FREE(removed);
        return ret;
    } else {
        return DEFAULT;
    }
}

TYPE TYPED(getFromForwardList)(TYPED(ForwardList)* list, size_t i) {
    TYPED(ForwardListElement)* current = list->head;
    for (size_t j = 0; j < i && current != NULL; j++) {
        current = current->next;
    }
    if (current != NULL) {
        return current->value;
    } else {
        return DEFAULT;
    }
}

void TYPED(setInForwardList)(TYPED(ForwardList)* list, size_t i, TYPE element) {
    TYPED(ForwardListElement)* current = list->head;
    for (size_t j = 0; j < i && current != NULL; j++) {
        current = current->next;
    }
    if (current != NULL) {
        current->value = element;
    }
}

TYPED(ForwardListIterator) TYPED(getForwardListIterator)(TYPED(ForwardList)* list) {
    TYPED(ForwardListIterator) ret = {
        .elem = list->head,
    };
    return ret;
}

bool TYPED(hasNextForwardList)(TYPED(ForwardListIterator)* iter) {
    return iter->elem != NULL;
}

TYPE TYPED(getNextForwardList)(TYPED(ForwardListIterator)* iter) {
    TYPE ret = iter->elem->value;
    iter->elem = iter->elem->next;
    return ret;
}

