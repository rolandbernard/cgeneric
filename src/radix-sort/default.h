
#include "../alloc.h"

#ifndef TYPE
#define TYPE unsigned int
#endif

#ifndef TYPED
#define TYPED(NAME) NAME ## Int
#endif

#ifndef KEY_SIZE
#define KEY_SIZE 256
#endif

// #define REVERSED_KEYS

#ifndef GET_KEY
#ifndef REVERSED_KEYS
#define GET_KEY(VALUE, N) ((VALUE >> (8 * (LENGTH - 1 - N))) & 0xff)
#else
#define GET_KEY(VALUE, N) ((VALUE >> (8 * N)) & 0xff)
#endif
#endif

// #define VARIABLE_LENGTH

#ifndef LENGTH
#ifndef VARIABLE_LENGTH
#define LENGTH 4
#else
#define LENGTH(VALUE) 4
#endif
#endif

