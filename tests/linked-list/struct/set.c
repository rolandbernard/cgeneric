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
    for (size_t i = 0; i < 100; i++) {
        pushToLinkedListTest(&list, TTT(0));
    }
    for (size_t i = 0; i < 100; i++) {
        setInLinkedListTest(&list, i, TTT(2*i));
        assert(getFromLinkedListTest(&list, i).a == TTT(2*(int)i).a);
    }
    deinitLinkedListTest(&list);
    return 0;
}

