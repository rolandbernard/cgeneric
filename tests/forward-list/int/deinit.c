// test:

#include <assert.h>

#include "forward-list/forward-list.c"

int main() {
    ForwardListInt list;
    initForwardListInt(&list);
    pushFrontToForwardListInt(&list, 42);
    deinitForwardListInt(&list);
    return 0;
}
