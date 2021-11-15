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

#define TTT(N) buildTest((N), (N)/(float)2, (N)/(double)4)

int main() {
    LinkedListTest list;
    initLinkedListTest(&list);
    for (int i = 0; i < 1000; i++) {
        pushToLinkedListTest(&list, TTT(2*i));
        assert(sizeOfLinkedListTest(&list) == (size_t)i + 1);
        assert(getFromLinkedListTest(&list, i).a == TTT(2*i).a);
    }
    for (int i = 999; i >= 0; i--) {
        Test val = popFromLinkedListTest(&list);
        assert(sizeOfLinkedListTest(&list) == (size_t)i);
        assert(val.b == TTT(2*i).b);
    }
    deinitLinkedListTest(&list);
    return 0;
}

