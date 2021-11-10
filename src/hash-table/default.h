
#include "../alloc.h"

#ifndef KEY
#define KEY int
#endif

#ifndef VALUE
#define VALUE int
#endif

#ifndef TYPED
#define TYPED(NAME) NAME ## IntToInt
#endif

#ifndef HASH
#include "../hash.h"
#define HASH(VALUE) hashBytes(&VALUE, sizeof(VALUE))
#endif

#ifndef EQUALS
#include <string.h>
#define EQUALS(FIRST, SECOND) (memcmp(&FIRST, &SECOND, sizeof(FIRST)) == 0)
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

#ifndef SHOULD_GROW
#define SHOULD_GROW(COUNT, CAPACITY) (CAPACITY == 0 || CAPACITY < COUNT * 2)
#endif

#ifndef SHOULD_SHRINK
#ifndef MINIMUM_CAPACITY
#define MINIMUM_CAPACITY 32
#endif
#define SHOULD_SHRINK(COUNT, CAPACITY) (SHRINK_FUNCTION(CAPACITY) > MINIMUM_CAPACITY && CAPACITY > COUNT * 4)
#endif

/* #define IMPLICIT_STATE */
#ifdef IMPLICIT_STATE
#ifndef IS_EMPTY
#define IS_EMPTY(KEY, VALUE) (KEY == (void*)0)
#endif
#ifndef IS_DELETED
#define IS_DELETED(KEY, VALUE) (KEY == (void*)1)
#endif
#ifndef IS_VALID
#define IS_VALID(KEY, VALUE) (!IS_EMPTY(KEY, VALUE) && !IS_DELETED(KEY, VALUE))
#endif
#ifndef SET_EMPTY
#define SET_EMPTY(KEY, VALUE) (KEY = (void*)0)
#endif
#ifndef SET_DELETED
#define SET_DELETED(KEY, VALUE) (KEY = (void*)1)
#endif
#endif

#ifndef DEFAULT
#define DEFAULT (VALUE)0
#endif

