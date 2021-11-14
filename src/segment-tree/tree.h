
#include "default.h"
#include <stddef.h>

size_t TYPED(sizeForSegmentTree)(size_t n);

TYPE* TYPED(createSegmentTree)(size_t n);

void TYPED(initSegmentTree)(TYPE* tree, size_t n);

void TYPED(copyToSegmentTree)(TYPE* tree, size_t n, TYPE* from);

TYPE TYPED(getFromSegmentTree)(TYPE* tree, size_t n, size_t i);

void TYPED(setInSegmentTree)(TYPE* tree, size_t n, size_t i, TYPE v);

TYPE TYPED(querySegmentTree)(TYPE* tree, size_t n, size_t from, size_t to);

