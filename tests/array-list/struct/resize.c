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
    resizeArrayListTest(&list, 5000);
    assert(list.data != NULL);
    assert(sizeOfArrayListTest(&list) == 5000);
    deinitArrayListTest(&list);
    return 0;
}

