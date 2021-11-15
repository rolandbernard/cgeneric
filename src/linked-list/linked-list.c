
#include <assert.h>
#include <stddef.h>

#include "linked-list.h"

void TYPED(initLinkedList)(TYPED(LinkedList)* list) {
    list->head = NULL;
    list->tail = NULL;
}

void TYPED(deinitLinkedList)(TYPED(LinkedList)* list) {
    TYPED(LinkedListElement)* current = list->head;
    while (current != NULL) {
        TYPED(LinkedListElement)* to_free = current;
        current = to_free->next;
        FREE(to_free);
    }
    list->head = NULL;
    list->tail = NULL;
}

size_t TYPED(sizeOfLinkedList)(TYPED(LinkedList)* list) {
    size_t size = 0;
    TYPED(LinkedListElement)* current = list->head;
    while (current != NULL) {
        size++;
        current = current->next;
    }
    return size;
}

void TYPED(pushToLinkedList)(TYPED(LinkedList)* list, TYPE element) {
    TYPED(LinkedListElement)* new = ALLOC(TYPED(LinkedListElement), 1);
    new->value = element;
    new->next = NULL;
    new->prev = list->tail;
    if (list->tail == NULL) {
        list->head = new;
        list->tail = new;
    } else {
        list->tail->next = new;
        list->tail = new;
    }
}

TYPE TYPED(popFromLinkedList)(TYPED(LinkedList)* list) {
    if (list->tail != NULL) {
        TYPED(LinkedListElement)* removed = list->tail;
        list->tail = removed->prev;
        if (list->tail == NULL) {
            list->head = NULL;
        } else {
            list->tail->next = NULL;
        }
        TYPE ret = removed->value;
        FREE(removed);
        return ret;
    } else {
        return DEFAULT;
    }
}

void TYPED(pushFrontToLinkedList)(TYPED(LinkedList)* list, TYPE element) {
    TYPED(LinkedListElement)* new = ALLOC(TYPED(LinkedListElement), 1);
    new->value = element;
    new->next = list->head;
    new->prev = NULL;
    if (list->head == NULL) {
        list->tail = new;
        list->head = new;
    } else {
        list->head->prev = new;
        list->head = new;
    }
}

TYPE TYPED(popFrontFromLinkedList)(TYPED(LinkedList)* list) {
    if (list->head != NULL) {
        TYPED(LinkedListElement)* removed = list->head;
        list->head = removed->next;
        if (list->head == NULL) {
            list->tail = NULL;
        } else {
            list->head->prev = NULL;
        }
        TYPE ret = removed->value;
        FREE(removed);
        return ret;
    } else {
        return DEFAULT;
    }
}

TYPE TYPED(getFromLinkedList)(TYPED(LinkedList)* list, size_t i) {
    TYPED(LinkedListElement)* current = list->head;
    for (size_t j = 0; j < i && current != NULL; j++) {
        current = current->next;
    }
    if (current != NULL) {
        return current->value;
    } else {
        return DEFAULT;
    }
}

void TYPED(setInLinkedList)(TYPED(LinkedList)* list, size_t i, TYPE element) {
    TYPED(LinkedListElement)* current = list->head;
    for (size_t j = 0; j < i && current != NULL; j++) {
        current = current->next;
    }
    if (current != NULL) {
        current->value = element;
    }
}

TYPED(LinkedListIterator) TYPED(getLinkedListIterator)(TYPED(LinkedList)* list) {
    TYPED(LinkedListIterator) ret = {
        .elem = list->head,
    };
    return ret;
}

bool TYPED(hasNextLinkedList)(TYPED(LinkedListIterator)* iter) {
    return iter->elem != NULL;
}

TYPE TYPED(getNextLinkedList)(TYPED(LinkedListIterator)* iter) {
    TYPE ret = iter->elem->value;
    iter->elem = iter->elem->next;
    return ret;
}

