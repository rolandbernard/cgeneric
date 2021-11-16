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

#define TTT(N) buildTest(N, N/(float)2, N/(double)4)

int main() {
    DequeTest list;
    initDequeTest(&list);
    // []
    pushToDequeTest(&list, TTT(12));
    pushToDequeTest(&list, TTT(13));
    pushToDequeTest(&list, TTT(14));
    pushToDequeTest(&list, TTT(15));
    pushToDequeTest(&list, TTT(16));
    // [12, 13, 14, 15, 16]
    assert(popFrontFromDequeTest(&list).a == TTT(12).a);
    assert(popFromDequeTest(&list).b == TTT(16).b);
    // [13, 14, 15]
    pushFrontToDequeTest(&list, TTT(20));
    pushFrontToDequeTest(&list, TTT(21));
    pushFrontToDequeTest(&list, TTT(22));
    // [22, 21, 20, 13, 14, 15]
    pushToDequeTest(&list, TTT(30));
    pushToDequeTest(&list, TTT(31));
    pushToDequeTest(&list, TTT(32));
    // [22, 21, 20, 13, 14, 15, 30, 31, 32]
    assert(popFromDequeTest(&list).c == TTT(32).c);
    assert(popFromDequeTest(&list).a == TTT(31).a);
    // [22, 21, 20, 13, 14, 15, 30]
    assert(popFrontFromDequeTest(&list).b == TTT(22).b);
    assert(popFrontFromDequeTest(&list).c == TTT(21).c);
    // [20, 13, 14, 15, 30]
    pushToDequeTest(&list, TTT(40));
    pushFrontToDequeTest(&list, TTT(41));
    // [41, 20, 13, 14, 15, 30, 40]
    assert(popFromDequeTest(&list).c == TTT(40).c);
    assert(popFromDequeTest(&list).a == TTT(30).a);
    assert(popFromDequeTest(&list).a == TTT(15).a);
    assert(popFromDequeTest(&list).a == TTT(14).a);
    assert(popFromDequeTest(&list).a == TTT(13).a);
    // [41, 20]
    assert(popFrontFromDequeTest(&list).b == TTT(41).b);
    assert(popFrontFromDequeTest(&list).b == TTT(20).b);
    // []
    deinitDequeTest(&list);
    return 0;
}

