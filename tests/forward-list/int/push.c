// test:

#include <assert.h>

#include "forward-list/forward-list.c"

int main() {
    ForwardListInt list;
    initForwardListInt(&list);
    for (size_t i = 0; i < 1000; i++) {
        pushFrontToForwardListInt(&list, 2*i);
        assert(sizeOfForwardListInt(&list) == i + 1);
        assert(getFromForwardListInt(&list, 0) == 2*(int)i);
    }
    deinitForwardListInt(&list);
    return 0;
}

