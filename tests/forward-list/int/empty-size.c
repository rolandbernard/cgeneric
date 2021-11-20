// test:

#include <assert.h>

#include "forward-list/forward-list.c"

int main() {
    ForwardListInt list;
    initForwardListInt(&list);
    assert(sizeOfForwardListInt(&list) == 0);
    deinitForwardListInt(&list);
    return 0;
}
