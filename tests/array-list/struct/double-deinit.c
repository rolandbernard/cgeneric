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
    deinitArrayListTest(&list);
    deinitArrayListTest(&list); // This must not give an error
    assert(list.data == NULL);
    return 0;
}
