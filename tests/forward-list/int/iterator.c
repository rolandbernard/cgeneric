// test:

#include <assert.h>

#include "forward-list/forward-list.c"

int main() {
    ForwardListInt list;
    initForwardListInt(&list);
    for (size_t i = 0; i < 1000; i++) {
        pushFrontToForwardListInt(&list, 2*i);
        assert(sizeOfForwardListInt(&list) == i + 1);
    }
    ForwardListIteratorInt it = getForwardListIteratorInt(&list);
    size_t i = 999;
    while (hasNextForwardListInt(&it)) {
        int v = getNextForwardListInt(&it);
        assert(v == 2*(int)i);
        i--;
    }
    deinitForwardListInt(&list);
    return 0;
}

