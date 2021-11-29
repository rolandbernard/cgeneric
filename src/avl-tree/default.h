
#include "../alloc.h"

#ifndef TYPE
#define TYPE int
#endif

#ifndef TYPED
#define TYPED(NAME) NAME ## Int
#endif

#ifndef LESS_THAN
#include <string.h>
#define LESS_THAN(FIRST, SECOND) (memcmp(&FIRST, &SECOND, sizeof(FIRST)) < 0)
#endif

// #define IS_SET

