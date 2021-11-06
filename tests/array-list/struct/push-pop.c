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
    for (int i = 0; i < 1000; i++) {
        TestStruct t = {
            .a = i,
            .b = 42,
            .c = 'a',
            .d = (double)i / 2,
        };
        pushToArrayListTest(&list, t);
        assert(sizeOfArrayListTest(&list) == (size_t)i + 1);
        assert(getFromArrayListTest(&list, i).a == t.a);
        assert(getFromArrayListTest(&list, i).b == t.b);
        assert(getFromArrayListTest(&list, i).c == t.c);
        assert(getFromArrayListTest(&list, i).d == t.d);
    }
    for (int i = 999; i >= 0; i--) {
        TestStruct val = popFromArrayListTest(&list);
        assert(sizeOfArrayListTest(&list) == (size_t)i);
        assert(val.a == i);
        assert(val.b == 42);
        assert(val.c == 'a');
        assert(val.d == (double)i / 2);
    }
    deinitArrayListTest(&list);
    return 0;
}

