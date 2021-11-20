// test:

#include <assert.h>

#include "forward-list/forward-list.c"

int main() {
    ForwardListInt list;
    initForwardListInt(&list);
    for (int i = 0; i < 1000; i++) {
        pushFrontToForwardListInt(&list, 2*i);
        assert(sizeOfForwardListInt(&list) == (size_t)i + 1);
        assert(getFromForwardListInt(&list, 0) == 2*i);
    }
    for (int i = 999; i >= 0; i--) {
        int val = popFrontFromForwardListInt(&list);
        assert(sizeOfForwardListInt(&list) == (size_t)i);
        assert(val == 2*i);
    }
    deinitForwardListInt(&list);
    return 0;
}

