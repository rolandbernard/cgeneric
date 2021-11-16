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

#include "deque/deque.c"

int main() {
    DequeTest list;
    initDequeTest(&list);
    pushToDequeTest(&list, buildTest(12, 4.2, 5.6));
    deinitDequeTest(&list);
    return 0;
}
