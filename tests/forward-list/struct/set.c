// test:

#include <assert.h>

typedef struct {
    int a;
    float b;
    double c;
} Test;

Test buildTest(int a, float b, double c) {
    Test ret = {a, b, c};
    return ret;
}

#define DEFAULT buildTest(0, 0, 0)
#define TYPE Test
#define TYPED(NAME) NAME ## Test

#include "forward-list/forward-list.c"

#define TTT(N) buildTest((N), (N)/(float)2, (N)/(double)4)

int main() {
    ForwardListTest list;
    initForwardListTest(&list);
    for (size_t i = 0; i < 100; i++) {
        pushFrontToForwardListTest(&list, TTT(0));
    }
    for (size_t i = 0; i < 100; i++) {
        setInForwardListTest(&list, i, TTT(2*i));
        assert(getFromForwardListTest(&list, i).a == TTT(2*(int)i).a);
    }
    deinitForwardListTest(&list);
    return 0;
}

