
#include "../alloc.h"

#ifndef TYPE
#define TYPE int
#endif

#ifndef TYPED
#define TYPED(NAME) NAME ## Int
#endif

#ifndef LESS_EQUAL
// This is used for comparison based sorts
#include <string.h>
#define LESS_EQUAL(FIRST, SECOND) (memcmp(&FIRST, &SECOND, sizeof(FIRST)) <= 0)
#endif

#ifndef MAX_INSERT_SORT
// The folowing are used for intro sort (maximum size for using insertion sort)
#define MAX_INSERT_SORT 16
#endif

#ifndef MAX_QUICK_SORT_DEPTH
// This times the floor of the log of n will be the max depth
#define MAX_QUICK_SORT_DEPTH 2
#endif

