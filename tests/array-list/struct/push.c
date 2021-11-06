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
    for (size_t i = 0; i < 1000; i++) {
        TestStruct t = {
            .a = i,
            .b = 42,
            .c = 'a',
            .d = (double)i / 2,
        };
        pushToArrayListTest(&list, t);
        assert(sizeOfArrayListTest(&list) == i + 1);
        assert(getFromArrayListTest(&list, i).a == t.a);
        assert(getFromArrayListTest(&list, i).b == t.b);
        assert(getFromArrayListTest(&list, i).c == t.c);
        assert(getFromArrayListTest(&list, i).d == t.d);
    }
    deinitArrayListTest(&list);
    return 0;
}

