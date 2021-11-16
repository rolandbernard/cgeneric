
#include "../alloc.h"

#ifndef TYPE
#define TYPE int
#endif

#ifndef TYPED
#define TYPED(NAME) NAME ## Int
#endif

#ifndef GROWTH_FUNCTION
#ifndef INITIAL_CAPACITY
#define INITIAL_CAPACITY 32
#endif
#define GROWTH_FUNCTION(N) (N == 0 ? INITIAL_CAPACITY : 3*N/2)
#endif

#ifndef SHRINK_FUNCTION
#define SHRINK_FUNCTION(N) (N/2)
#endif

#ifndef SHOULD_SHRINK
#define SHOULD_SHRINK(COUNT, CAPACITY) (CAPACITY > COUNT * 3)
#endif

