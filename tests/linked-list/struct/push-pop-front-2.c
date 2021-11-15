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

#include "linked-list/linked-list.c"

#define TTT(N) buildTest(N, N/(float)2, N/(double)4)

int main() {
    LinkedListTest list;
    initLinkedListTest(&list);
    // []
    pushToLinkedListTest(&list, TTT(12));
    pushToLinkedListTest(&list, TTT(13));
    pushToLinkedListTest(&list, TTT(14));
    pushToLinkedListTest(&list, TTT(15));
    pushToLinkedListTest(&list, TTT(16));
    // [12, 13, 14, 15, 16]
    assert(popFrontFromLinkedListTest(&list).a == TTT(12).a);
    assert(popFromLinkedListTest(&list).b == TTT(16).b);
    // [13, 14, 15]
    pushFrontToLinkedListTest(&list, TTT(20));
    pushFrontToLinkedListTest(&list, TTT(21));
    pushFrontToLinkedListTest(&list, TTT(22));
    // [22, 21, 20, 13, 14, 15]
    pushToLinkedListTest(&list, TTT(30));
    pushToLinkedListTest(&list, TTT(31));
    pushToLinkedListTest(&list, TTT(32));
    // [22, 21, 20, 13, 14, 15, 30, 31, 32]
    assert(popFromLinkedListTest(&list).c == TTT(32).c);
    assert(popFromLinkedListTest(&list).a == TTT(31).a);
    // [22, 21, 20, 13, 14, 15, 30]
    assert(popFrontFromLinkedListTest(&list).b == TTT(22).b);
    assert(popFrontFromLinkedListTest(&list).c == TTT(21).c);
    // [20, 13, 14, 15, 30]
    pushToLinkedListTest(&list, TTT(40));
    pushFrontToLinkedListTest(&list, TTT(41));
    // [41, 20, 13, 14, 15, 30, 40]
    assert(popFromLinkedListTest(&list).c == TTT(40).c);
    assert(popFromLinkedListTest(&list).a == TTT(30).a);
    assert(popFromLinkedListTest(&list).a == TTT(15).a);
    assert(popFromLinkedListTest(&list).a == TTT(14).a);
    assert(popFromLinkedListTest(&list).a == TTT(13).a);
    // [41, 20]
    assert(popFrontFromLinkedListTest(&list).b == TTT(41).b);
    assert(popFrontFromLinkedListTest(&list).b == TTT(20).b);
    // []
    deinitLinkedListTest(&list);
    return 0;
}

