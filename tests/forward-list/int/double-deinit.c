// test:

#include <assert.h>

#include "forward-list/forward-list.c"

int main() {
    ForwardListInt list;
    initForwardListInt(&list);
    deinitForwardListInt(&list);
    deinitForwardListInt(&list); // This must not give an error
    return 0;
}
