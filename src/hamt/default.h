
#include "../alloc.h"

#ifndef KEY
#define KEY int
#endif

#ifndef VALUE
#define VALUE int
#endif

#ifndef TYPED
#define TYPED(NAME) NAME##IntToInt
#endif

#ifndef HASH
#include "../hash.h"
#define HASH(VALUE) hashBytes(&VALUE, sizeof(VALUE))
#endif

#ifndef EQUALS
#include <string.h>
#define EQUALS(FIRST, SECOND) (memcmp(&FIRST, &SECOND, sizeof(FIRST)) == 0)
#endif

#ifndef DEFAULT
#define DEFAULT (VALUE)0
#endif
