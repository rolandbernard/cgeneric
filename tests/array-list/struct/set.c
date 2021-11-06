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
    resizeArrayListTest(&list, 100);
    for (size_t i = 0; i < 100; i++) {
        TestStruct t = {
            .a = i,
            .b = 42,
            .c = 'a',
            .d = (double)i / 2,
        };
        setInArrayListTest(&list, i, t);
        assert(getFromArrayListTest(&list, i).a == t.a);
        assert(getFromArrayListTest(&list, i).b == t.b);
        assert(getFromArrayListTest(&list, i).c == t.c);
        assert(getFromArrayListTest(&list, i).d == t.d);
    }
    deinitArrayListTest(&list);
    return 0;
}

