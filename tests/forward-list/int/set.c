// test:

#include <assert.h>

#include "forward-list/forward-list.c"

int main() {
    ForwardListInt list;
    initForwardListInt(&list);
    for (size_t i = 0; i < 100; i++) {
        pushFrontToForwardListInt(&list, 0);
    }
    for (size_t i = 0; i < 100; i++) {
        setInForwardListInt(&list, i, 2*i);
        assert(getFromForwardListInt(&list, i) == 2 * (int)i);
    }
    deinitForwardListInt(&list);
    return 0;
}

