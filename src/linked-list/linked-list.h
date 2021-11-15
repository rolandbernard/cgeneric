
#include <stddef.h>
#include <stdbool.h>

#include "default.h"

typedef struct TYPED(LinkedList) TYPED(LinkedList);

typedef struct TYPED(LinkedListElement) TYPED(LinkedListElement);

struct TYPED(LinkedListElement) {
    TYPED(LinkedListElement)* next;
    TYPED(LinkedListElement)* prev;
    TYPE value;
};

struct TYPED(LinkedList) {
    TYPED(LinkedListElement)* head;
    TYPED(LinkedListElement)* tail;
};

void TYPED(initLinkedList)(TYPED(LinkedList)* list);

void TYPED(deinitLinkedList)(TYPED(LinkedList)* list);

size_t TYPED(sizeOfLinkedList)(TYPED(LinkedList)* list);

void TYPED(pushToLinkedList)(TYPED(LinkedList)* list, TYPE element);

TYPE TYPED(popFromLinkedList)(TYPED(LinkedList)* list);

void TYPED(pushFrontToLinkedList)(TYPED(LinkedList)* list, TYPE element);

TYPE TYPED(popFrontFromLinkedList)(TYPED(LinkedList)* list);

TYPE TYPED(getFromLinkedList)(TYPED(LinkedList)* list, size_t i);

void TYPED(setInLinkedList)(TYPED(LinkedList)* list, size_t i, TYPE element);

typedef struct TYPED(LinkedListIterator) TYPED(LinkedListIterator);

struct TYPED(LinkedListIterator) {
    TYPED(LinkedListElement)* elem;
};

TYPED(LinkedListIterator) TYPED(getLinkedListIterator)(TYPED(LinkedList)* list);

bool TYPED(hasNextLinkedList)(TYPED(LinkedListIterator)* iter);

TYPE TYPED(getNextLinkedList)(TYPED(LinkedListIterator)* iter);

