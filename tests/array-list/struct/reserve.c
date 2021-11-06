// test:

#include <assert.h>

typedef struct {
    int a;
    short b;
    char c;
    double d;
} TestStruct;

#define TYPE TestStruct
#define TYPED(NAME) NAME ## Test

#include "array-list/array-list.c"

int main() {
    ArrayListTest list;
    initArrayListTest(&list);
    reserveArrayListTest(&list, 50000);
    assert(list.data != NULL);
    assert(list.capacity >= 50000);
    deinitArrayListTest(&list);
    return 0;
}

