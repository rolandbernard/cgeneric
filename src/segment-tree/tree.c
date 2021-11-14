
#include "tree.h"

#define LSB(N) ((N) & -(N))

size_t TYPED(sizeForSegmentTree)(size_t n) {
    if (n == LSB(n)) {
        return 2*n - 1;
    } else {
        do {
            n -= LSB(n);
        } while (n != LSB(n));
        return 4*n - 1;
    }
}

TYPE* TYPED(createSegmentTree)(size_t n) {
    size_t size = TYPED(sizeForSegmentTree)(n);
    TYPE* values =  ALLOC(TYPE, size);
    for (size_t i = 0; i < size; i++) {
        values[i] = EMPTY;
    }
    return values;
}

void TYPED(initSegmentTree)(TYPE* tree, size_t n) {
    size_t size = TYPED(sizeForSegmentTree)(n);
    for (size_t i = 0; i < size; i++) {
        tree[i] = EMPTY;
    }
}

void TYPED(copyToSegmentTree)(TYPE* tree, size_t n, TYPE* from) {
    size_t size = TYPED(sizeForSegmentTree)(n);
    for (size_t i = 0; i < n; i++) {
        tree[size / 2 + i] = from[i];
    }
    for (size_t i = size / 2; i > 0;) {
        i--;
        size_t left = 2*(i + 1) - 1; 
        size_t right = 2*(i + 1); 
        tree[i] = COMBINE(tree[left], tree[right]);
    }
}

TYPE TYPED(getFromSegmentTree)(TYPE* tree, size_t n, size_t i) {
    size_t size = TYPED(sizeForSegmentTree)(n);
    return tree[size / 2 + i];
}

void TYPED(setInSegmentTree)(TYPE* tree, size_t n, size_t i, TYPE v) {
    size_t size = TYPED(sizeForSegmentTree)(n);
    size_t c = size / 2 + i;
    tree[c] = v;
    while (c != 0) {
        c = (c + 1) / 2 - 1;
        size_t left = 2*(c + 1) - 1; 
        size_t right = 2*(c + 1); 
        tree[c] = COMBINE(tree[left], tree[right]);
    }
}

static TYPE TYPED(segmentTreeQueryHelper)(TYPE* tree, size_t i, size_t from, size_t to, size_t l, size_t r) {
    if (l >= to || r <= from) {
        return EMPTY;
    } else if (l >= from && r <= to) {
        return tree[i];
    } else {
        size_t left = 2*(i + 1) - 1; 
        size_t right = 2*(i + 1); 
        return COMBINE(
            TYPED(segmentTreeQueryHelper)(tree, left, from, to, l, (l + r) / 2),
            TYPED(segmentTreeQueryHelper)(tree, right, from, to, (l + r) / 2, r)
        );
    }
}

TYPE TYPED(querySegmentTree)(TYPE* tree, size_t n, size_t from, size_t to) {
    if (from >= to) {
        return EMPTY;
    } else if (from + 1 == to) {
        return TYPED(getFromSegmentTree)(tree, n, from);
    } else {
        size_t size = TYPED(sizeForSegmentTree)(n);
        return TYPED(segmentTreeQueryHelper)(tree, 0, from, to, 0, (size + 1) / 2);
    }
}

#undef LSB

