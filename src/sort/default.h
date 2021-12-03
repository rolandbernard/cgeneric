
#include "../alloc.h"

#ifndef TYPE
#define TYPE int
#endif

#ifndef TYPED
#define TYPED(NAME) NAME ## Int
#endif

#ifndef LESS_EQUAL
#include <string.h>
#define LESS_EQUAL(FIRST, SECOND) (memcmp(&FIRST, &SECOND, sizeof(FIRST)) <= 0)
#endif

#ifndef MAX_INSERT_SORT
#define MAX_INSERT_SORT 16
#endif

#ifndef MAX_QUICK_SORT_DEPTH
#define MAX_QUICK_SORT_DEPTH 2
#endif

