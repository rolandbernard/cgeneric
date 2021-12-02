
#include "../alloc.h"

#ifndef KEY
#define KEY int
#endif

#ifndef TYPED
#define TYPED(NAME) NAME ## IntToInt
#endif

#ifndef LENGTH
#define LENGTH(VALUE) sizeof(KEY)
#endif

#ifndef GET_KEY
#define GET_KEY(VALUE, N) (((unsigned char*)&VALUE))[N]
#endif

#ifndef KEY_SIZE
#define KEY_SIZE 256
#endif

#ifndef IS_SET
#ifndef VALUE
#define VALUE int
#endif
// #define IMPLICIT_STATE
#ifdef IMPLICIT_STATE
#ifndef IS_VALID
#define IS_VALID(VALUE) (VALUE != NULL)
#endif
#ifdef SET_INVALID
#define SET_INVALID(VALUE) VALUE = NULL
#endif
#endif
#ifndef DEFAULT
#define DEFAULT (VALUE)0
#endif
#endif

