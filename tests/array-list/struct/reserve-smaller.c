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
    resizeArrayListTest(&list, 500);
    reserveArrayListTest(&list, 50);
    assert(list.capacity >= 500);
    assert(sizeOfArrayListTest(&list) == 500);
    deinitArrayListTest(&list);
    return 0;
}

