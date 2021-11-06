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
    TestStruct t = {
        .a = 1,
        .b = 2,
        .c = 'a',
        .d = 4.2,
    };
    pushToArrayListTest(&list, t);
    assert(list.data != NULL);
    deinitArrayListTest(&list);
    assert(list.data == NULL);
    return 0;
}
