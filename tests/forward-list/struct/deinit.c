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

int main() {
    ForwardListTest list;
    initForwardListTest(&list);
    pushFrontToForwardListTest(&list, buildTest(12, 4.2, 5.6));
    deinitForwardListTest(&list);
    return 0;
}
